//
// Created by patri on 4/20/2018.
//

#ifndef RHYTHMICPROGRAMMING_RENDERSERVICE_H
#define RHYTHMICPROGRAMMING_RENDERSERVICE_H

#include <vector>
#include <android/native_window.h>
#include <android/asset_manager.h>
#include <chrono>
#include "../glm/detail/type_mat.hpp"
#include "../render/Viewport.h"
#include "../render/Scene.h"
#include "../sprite/Sprite.h"
#include "../render/Scene2D.h"
#include "../render/OpenGLContext.h"
#include "../sprite/StringRenderData.cpp"
#include "../sprite/SpriteString.h"
#include "../properties.h"
#include "../System.h"
#include "ServiceManager.h"

using namespace std::chrono;

class RenderService : public Service {
private:
    OpenGLContext* _openGLContext = nullptr;
    Viewport* _viewport = nullptr;

    Scene2D* _backgroundScene;
    Scene2D* _foregroundScene;
    AAssetManager* _assetManager;
    std::map<const char*, SpriteString*> _stringMap;

    void _renderString(StringRenderData* pData);

    void _unrenderString(std::string& renderKey);

    void _clearStringMap();

public:
    RenderService();

    ~RenderService();

    void BuildRenderingEnvironment(ANativeWindow* window);

    void Render();

    void SetViewport(Viewport* viewport);

    void SetSceneColor(const glm::vec3& color);

    void Listener(Message* message) override;
};


#endif //RHYTHMICPROGRAMMING_RENDERSERVICE_H
