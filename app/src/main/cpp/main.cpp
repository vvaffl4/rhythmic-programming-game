/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/*
 * COMPILER VARIABLES
 */
#define GLM_FORCE_MESSAGES
#define GLM_FORCE_CXX11

//BEGIN_INCLUDE(all)
#include <dlfcn.h>
#include <initializer_list>
#include <sstream>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <string>
#include <jni.h>
#include <android/log.h>
#include <unistd.h>
#include <time.h>

#include <EGL/egl.h>
#include <GLES3/gl31.h>

#include <android/sensor.h>
#include <android_native_app_glue.h>

// For Native audio
#include <SLES/OpenSLES_Android.h>

// For OpenGLContext=
#include "render/OpenGLContext.h"

#include "sprite/SpritesheetFactory.h"
#include "sprite/SpritesheetFontFactory.h"

// For InputHandlingService
#include "input/InputHandler.h"
#include "render/Model.h"
#include "render/Scene.h"
#include "render/Scene2D.h"
#include "services/RenderService.h"
#include "sprite/Sprite.h"
#include "uiobjects/BeatHitDetectionButton.h"
#include "services/UIService.h"
#include "uiobjects/BeatLane.h"
#include "ResourceManager.h"
#include "uiobjects/StartButton.h"
#include "System.h"
#include "sprite/SpriteString.h"

#include "render/ShaderManager.h"
#include "screens/TitleScreen.h"

/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

// Wrapper function around system time;
static double time_now_s(void) {
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return res.tv_sec + (double) res.tv_nsec / 1e9;
}

static double time_now_ms(void) {
    return 1000.0 * time_now_s();
}

/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;
    int animating = 0;
    bool paused = false;
    struct saved_state state;
    System system;
    InputHandler inputHandler;
    bool game_initialized = false;
    double currentTime = time_now_s();
};

class EngineHolder {
private:
    struct engine* _engine = nullptr;

    EngineHolder() {}

public:
    EngineHolder(EngineHolder const&) = delete;

    void operator=(EngineHolder const&) = delete;

    static EngineHolder& GetIntance() {
        static EngineHolder instance;
        return instance;
    }

    void Hold(struct engine* engine) { _engine = engine; }

    struct engine* GetEngine() { return _engine; }
};

static void engine_init_game(struct engine* engine) {
    if (engine->game_initialized) return;

    engine->inputHandler.UseDimensions(
            ANativeWindow_getWidth(engine->app->window),
            ANativeWindow_getHeight(engine->app->window)
    );

    ServiceManager::GetInstance().Send(new Message{
            CREATE_BUILDENVIRONMENT,
            &engine->system
    });

    ServiceManager::GetInstance().Send(new Message{
            SET_UISCENE,
            new TitleScreen(0, 0)
    });

    ServiceManager::GetInstance().Send(new Message{
            SWITCH_SCREEN,
            NULL
    });

    engine->game_initialized = true;
}

static void AutoHideNavBar(struct android_app* state) {
    JNIEnv* env;
    state->activity->vm->AttachCurrentThread(&env, NULL);

    jclass activityClass = env->FindClass("android/app/NativeActivity");
    jmethodID getWindow = env->GetMethodID(activityClass, "getWindow", "()Landroid/view/Window;");

    jclass windowClass = env->FindClass("android/view/Window");
    jmethodID getDecorView = env->GetMethodID(windowClass, "getDecorView", "()Landroid/view/View;");

    jclass viewClass = env->FindClass("android/view/View");
    jmethodID setSystemUiVisibility = env->GetMethodID(viewClass, "setSystemUiVisibility", "(I)V");

    jobject window = env->CallObjectMethod(state->activity->clazz, getWindow);

    jobject decorView = env->CallObjectMethod(window, getDecorView);

    jfieldID flagLayoutStableID = env->GetStaticFieldID(viewClass, "SYSTEM_UI_FLAG_LAYOUT_STABLE",
                                                        "I");
    jfieldID flagLayoutHideNavigationID = env->GetStaticFieldID(viewClass,
                                                                "SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION",
                                                                "I");
    jfieldID flagLayoutFullscreenID = env->GetStaticFieldID(viewClass,
                                                            "SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN",
                                                            "I");
    jfieldID flagHideNavigationID = env->GetStaticFieldID(viewClass,
                                                          "SYSTEM_UI_FLAG_HIDE_NAVIGATION", "I");
    jfieldID flagFullscreenID = env->GetStaticFieldID(viewClass, "SYSTEM_UI_FLAG_FULLSCREEN", "I");
    jfieldID flagImmersiveID = env->GetStaticFieldID(viewClass, "SYSTEM_UI_FLAG_IMMERSIVE_STICKY",
                                                     "I");

    int flagLayoutStable = env->GetStaticIntField(viewClass, flagLayoutStableID);
    int flagLayoutHideNavigation = env->GetStaticIntField(viewClass, flagLayoutHideNavigationID);
    int flagLayoutFullscreen = env->GetStaticIntField(viewClass, flagLayoutFullscreenID);
    int flagHideNavigation = env->GetStaticIntField(viewClass, flagHideNavigationID);
    int flagFullscreen = env->GetStaticIntField(viewClass, flagFullscreenID);
    int flagImmersive = env->GetStaticIntField(viewClass, flagImmersiveID);
    int flag = flagLayoutStable | flagLayoutHideNavigation | flagLayoutFullscreen |
               flagHideNavigation | flagFullscreen | flagImmersive;

    env->CallVoidMethod(decorView, setSystemUiVisibility, flag);

    state->activity->vm->DetachCurrentThread();
}

/**
 * Initialize an EGL context for the current display.
 */
static int engine_init_display(struct engine* engine) {
    // initialize OpenGL ES and EGL

    engine->system.nativeWindow = engine->app->window;
    engine->system.nativeActivity = engine->app->activity;
    engine->system.assetManager = engine->app->activity->assetManager;

    ServiceManager::GetInstance().Send(new Message{
            MessageType::ON_INIT_DISPLAY,
            &engine->system
    });

    return 0;
}

static void engine_deinit_game(struct engine* engine) {
    ServiceManager::GetInstance().DestroyServices();
    engine->game_initialized = false;
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engine_term_display(struct engine* engine) {
    engine->animating = 0;

    SpritesheetFontFactory::GetInstance().ClearCache();
    ShaderManager::GetInstance().ClearCache();

    ServiceManager::GetInstance().Send(new Message{
            MessageType::ON_TERM_DISPLAY,
            nullptr
    });
}


/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    struct engine* engine = (struct engine*) app->userData;

    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            engine->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*) engine->app->savedState) = engine->state;
            engine->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (engine->app->window != NULL) {
                ShaderManager::GetInstance().SetAssetManager(engine->app->activity->assetManager);
                ServiceManager::GetInstance().CreateServices();
                engine_init_display(engine);
            }

            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine_term_display(engine);
            engine_deinit_game(engine);
            break;
        case APP_CMD_GAINED_FOCUS:
            ShaderManager::GetInstance().SetAssetManager(engine->app->activity->assetManager);
            engine_init_game(engine);
            engine->animating = 1;
            break;
        case APP_CMD_LOST_FOCUS:
            // Also Stop animating.
            engine->animating = 0;
            break;
        case APP_CMD_PAUSE:
            engine->paused = true;
            break;
        case APP_CMD_RESUME:
            engine->paused = false;
            break;
    }
}

static int32_t engine_handle_native_input(struct android_app* app, AInputEvent* event) {
    engine* engine = EngineHolder::GetIntance().GetEngine();
    return engine->inputHandler.Handle(event);
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {
    struct engine engine;

    AutoHideNavBar(state);
    engine.inputHandler = InputHandler();
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_native_input;
    engine.app = state;
    engine.animating = 1;

    EngineHolder::GetIntance().Hold(&engine);

    if (state->savedState != NULL) {
        // We are starting with a previous saved state; restore from it.
        engine.state = *(struct saved_state*) state->savedState;
    }

    // loop waiting for stuff to do.

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident = ALooper_pollAll(
                engine.animating ? 0 : -1,
                NULL,
                &events,
                (void**) &source)) >= 0) {

            // Process this event.
            if (source != NULL) source->process(state, source);

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {

            }

            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                engine_term_display(&engine);
                return;
            }
        }

        if (engine.animating && !engine.paused && engine.game_initialized) {
            double now = time_now_s();
            double deltaTime = now - engine.currentTime;
            engine.currentTime = now;

            ServiceManager::GetInstance().Send(new Message{
                    MessageType::ON_LOGIC_LOOP,
                    &deltaTime
            });

            // Done with events; draw next animation frame.
            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.
            ServiceManager::GetInstance().Send(new Message{
                    MessageType::RENDER_FRAME,
                    nullptr
            });

        }

        if (engine.paused) {
            // Prevent the game from burning a hole in your pocket
            usleep(100);
        }
    }
}
//END_INCLUDE(all)
