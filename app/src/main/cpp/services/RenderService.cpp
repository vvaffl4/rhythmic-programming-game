//
// Created by patri on 4/20/2018.
//

#include "RenderService.h"

RenderService::RenderService() : Service() {
    ServiceManager::GetInstance().GetObservable()->AddObserver(_observer);
}

RenderService::~RenderService() {}

void RenderService::BuildRenderingEnvironment(ANativeWindow* window) {
    int width = ANativeWindow_getWidth(window);
    int height = ANativeWindow_getHeight(window);

    /*
     * Create Scenes and add Models
     */
    _backgroundScene = new Scene2D(
            0,
            Properties.WIDTH,//width,
            Properties.HEIGHT,//height,
            0);

    /*
     * Size doesn't matter, the position will always be kept within the boundaries of the screen
     */
    _foregroundScene = new Scene2D(
            0,
            Properties.WIDTH, //width,
            Properties.HEIGHT, //height,
            0);

    /*
     * Create viewport
     */
    Viewport* viewport = new Viewport(
            0,
            0,
            static_cast<short>(width),
            static_cast<short>(height));

    SetViewport(viewport);
}

void RenderService::Listener(Message* message) {
    switch (message->type) {
        case MessageType::RENDER_FRAME: {
            Render();
            break;
        }
        case MessageType::SET_SCENE_COLOR: {
            SetSceneColor(*(static_cast<glm::vec3*>(message->pointer)));
            break;
        }
        case MessageType::ADD_OBJECT2D: {
            _foregroundScene->AddModel(static_cast<Model*>(message->pointer));
            break;
        }
        case MessageType::REMOVE_OBJECT2D: {
            _foregroundScene->RemoveModel(static_cast<Model*>(message->pointer));
            break;
        }
        case MessageType::ADD_BACKGROUND_OBJECT2D: {
            _backgroundScene->AddModel(static_cast<Model*>(message->pointer));
            break;
        }
        case MessageType::REMOVE_BACKGROUND_OBJECT2D: {
            _backgroundScene->RemoveModel(static_cast<Model*>(message->pointer));
            break;
        }
        case MessageType::RENDER_STRING: {
            _renderString(static_cast<StringRenderData*>(message->pointer));
            break;
        }
        case MessageType::UNRENDER_STRING: {
            std::string renderKey = *(static_cast<std::string*> (message->pointer));
            _unrenderString(renderKey);
            break;
        }
        case MessageType::ON_INIT_DISPLAY: {
            System* system = static_cast<System*> (message->pointer);

            _openGLContext = new OpenGLContext();
            _openGLContext->CreateOpenGLContext(system->nativeWindow);
            break;
        }
        case MessageType::ON_TERM_DISPLAY: {
            _clearStringMap();

            if (_openGLContext != nullptr) {
                _openGLContext->DestroyOpenGLContext();
                delete _openGLContext;
                _openGLContext = nullptr;
            }
            break;
        }
        case MessageType::CREATE_BUILDENVIRONMENT: {
            System* system = static_cast<System*> (message->pointer);
            BuildRenderingEnvironment(system->nativeWindow);
            _assetManager = system->assetManager;
            break;
        }
        case MessageType::UNRENDER_ALL_STRINGS: {
            _clearStringMap();
            break;
        }
        default: {
            break;
        }
    }
}

void RenderService::Render() {
    if (_viewport == nullptr) return;
    if (_openGLContext == nullptr) return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _viewport->use();

    _backgroundScene->Render();
    _foregroundScene->Render();

    _openGLContext->SwapBuffers();
}

void RenderService::SetViewport(Viewport* viewport) {
    _viewport = viewport;
}

void RenderService::SetSceneColor(const glm::vec3& color) {

    _foregroundScene->SetColor(color);
    _backgroundScene->SetColor(color);
}

void RenderService::_renderString(StringRenderData* pData) {
    SpriteString* previousString = _stringMap[pData->key];
    if (previousString && previousString != nullptr) {
        delete previousString;
    }

    SpriteString* spriteString = new SpriteString(_assetManager, pData->font, pData->string);
    spriteString->SetPosition(pData->x, pData->y, pData->alignment, pData->scale);
    spriteString->SetRotation(pData->rotation);
    spriteString->ScaleSprites(pData->scale);

    spriteString->RenderAdd(_foregroundScene);
    _stringMap[pData->key] = spriteString;
}

void RenderService::_clearStringMap() {
    for (auto it = _stringMap.begin(); it != _stringMap.end(); it++) {
        SpriteString* spriteString = it->second;
        delete spriteString;
        spriteString = nullptr;
    }
    _stringMap.clear();
}

void RenderService::_unrenderString(std::string& renderKey) {
    const char* c_renderKey = renderKey.c_str();

    for (auto it = _stringMap.begin(); it != _stringMap.end(); it++) {
        if (std::strcmp(it->first, c_renderKey)) {
            delete it->second;
            _stringMap.erase(it);
            break;
        }
    }
}

