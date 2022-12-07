//
// Created by patri on 4/24/2018.
//

#include "ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

// Used for checking if textures fail to load
#define RESOURCE_MANAGER_LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "ResourceManager", __VA_ARGS__))

ResourceManager::ResourceManager() :
        _textures(std::map<std::string, Texture*>()),
        _meshes(std::map<std::string, Mesh*>()),
        _shaders(std::map<std::string, Shader*>()) {}

Texture* ResourceManager::CreateTextureObjectFromAsset(AAssetManager* assetManager,
                                                       const char* path) {

    AAsset* asset = AAssetManager_open(assetManager, path, AASSET_MODE_BUFFER);

    off_t size = AAsset_getLength(asset);
    std::vector<uint8_t> buffer = std::vector<uint8_t>(static_cast<unsigned long>(size));

    int64_t readSize = AAsset_read(asset, buffer.data(), buffer.size());

    AAsset_close(asset);

    if (size != readSize) return 0;

    GLuint id = 0;

    int width;
    int height;
    int components;

    uint8_t* data = stbi_load_from_memory(
            buffer.data(),
            static_cast<int>(buffer.size()),
            &width,
            &height,
            &components,
            4);
    if (data) {
        /*
        * Load image data into texture
        */
        GLenum format = 0;
        if (components == 1)
            format = GL_RED;
        else if (components == 3)
            format = GL_RGBA;
        else if (components == 4)
            format = GL_RGBA;
        else
            return 0;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
    } else {
        RESOURCE_MANAGER_LOGI("Failed to load texture");
    }
    /*
    * Release loaded image
    */
    stbi_image_free(data);

    Texture* texture = new Texture(id, static_cast<unsigned int>(width),
                                   static_cast<unsigned int>(height));

    return texture;
}

void ResourceManager::ReleaseResources() {
    for (auto textureIt = _textures.rbegin(); textureIt != _textures.rend(); ++textureIt) {
        delete textureIt->second;
    }
    _textures.clear();

    for (auto particleAnimationIt = _particleAnimations.rbegin();
         particleAnimationIt != _particleAnimations.rend(); ++particleAnimationIt) {
        delete particleAnimationIt->second;
    }
    _particleAnimations.clear();
}

void ResourceManager::SetResource(const std::string& identifier, Texture* resource) {
    _textures.insert(std::make_pair(identifier, resource));
}

void ResourceManager::SetResource(const std::string& identifier, ParticleAnimation* resource) {
    _particleAnimations.insert(std::make_pair(identifier, resource));
}

Texture* ResourceManager::GetTexture(const std::string& identifier) {
    return _textures[identifier];
}

ParticleAnimation* ResourceManager::GetParticleAnimation(const std::string& identifier) {
    return _particleAnimations[identifier];
}


