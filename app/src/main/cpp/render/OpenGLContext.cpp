//
// Created by patri on 4/18/2018.
//

#include "OpenGLContext.h"

void OpenGLContext::CreateOpenGLContext(ANativeWindow* window) {
    // initialize OpenGL ES and EGL

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };

    const EGLint context_attrib_list[] = {
            // request a context using Open GL ES 2.0
            EGL_CONTEXT_CLIENT_VERSION, 3,
            EGL_NONE
    };

    EGLint width;
    EGLint height;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;


    const char* egl_version = eglQueryString(EGL_NO_DISPLAY, EGL_VERSION);

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    EGLint eglMajVers, eglMinVers; //ADDED

    eglInitialize(display, &eglMajVers, &eglMinVers);

    /* Here, the application chooses the configuration it desires.
     * find the best match if possible, otherwise use the very first one
     */
    eglChooseConfig(
            display,
            attribs,
            &config,
            1,
            &numConfigs);

    surface = eglCreateWindowSurface(
            display,
            config,
            window,
            NULL);

    context = eglCreateContext(
            display,
            config,
            NULL,
            context_attrib_list);

    if (context == EGL_NO_CONTEXT) {
        EGLint error = eglGetError();

        if (error == EGL_BAD_CONFIG) {

        }
    }

    if (eglMakeCurrent(
            display,
            surface,
            surface,
            context) == EGL_FALSE) {
    }

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */

    eglQuerySurface(display, surface, EGL_WIDTH, &width);
    eglQuerySurface(display, surface, EGL_HEIGHT, &height);

    _display = display;
    _context = context;
    _surface = surface;
    _width = width;
    _height = height;

    // Check openGL on the system
    auto opengl_info = {GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS};
    for (auto name : opengl_info) {
        auto info = glGetString(name);
    }

    // Initialize GL state.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLContext::DestroyOpenGLContext() {
    if (_display != EGL_NO_DISPLAY) {
        eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (_context != EGL_NO_CONTEXT) {
            eglDestroyContext(_display, _context);
        }
        if (_surface != EGL_NO_SURFACE) {
            eglDestroySurface(_display, _surface);
        }
        eglTerminate(_display);
    }

    _display = EGL_NO_DISPLAY;
    _context = EGL_NO_CONTEXT;
    _surface = EGL_NO_SURFACE;
}

void OpenGLContext::SwapBuffers() {
    eglSwapBuffers(_display, _surface);
}
