//
// Created by patri on 4/24/2018.
//

#ifndef RHYTHMICPROGRAMMING_RESOURCEMANAGER_H
#define RHYTHMICPROGRAMMING_RESOURCEMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <GLES3/gl31.h>
#include <android/asset_manager.h>
#include <android/log.h>
#include "render/Texture.h"
#include "render/Mesh.h"
#include "render/Shader.h"
#include "particles/ParticleAnimation.h"

class ResourceManager {
private:
    std::map<std::string, Texture*> _textures;
    std::map<std::string, ParticleAnimation*> _particleAnimations;

    std::map<std::string, Mesh*> _meshes;
    std::map<std::string, Shader*> _shaders;

    ResourceManager();

public:
    ResourceManager(ResourceManager const&) = delete;

    void operator=(ResourceManager const&) = delete;

    static ResourceManager& GetInstance() {
        static ResourceManager instance;
        return instance;
    }

    static Texture* CreateTextureObjectFromAsset(AAssetManager* assetManager, const char* path);

    void ReleaseResources();

    void SetResource(const std::string& identifier, Texture* resource);

    void SetResource(const std::string& identifier, ParticleAnimation* resource);

    Texture* GetTexture(const std::string& identifier);

    ParticleAnimation* GetParticleAnimation(const std::string& identifier);
};


#endif //RHYTHMICPROGRAMMING_RESOURCEMANAGER_H
