//
// Created by michelle on 01/06/18.
//

#include "ShaderManager.h"

void ShaderManager::SetAssetManager(AAssetManager* assetManager) {
    _assetManager = assetManager;
}

Shader* ShaderManager::_internalGetShader(std::string& name) {
    Shader* shader = _cache[name];
    if (shader) return shader;
    if (_assetManager == nullptr) return nullptr;

    ShaderSource source(_assetManager, name);
    source.KeepShader();
    shader = source.GetShader();
    _cache[name] = shader;

    return shader;
}

void ShaderManager::UseShader(std::string name) {
    Shader* shader = _internalGetShader(name);
    if (shader != nullptr) shader->Use();
}

Shader* ShaderManager::GetShader(std::string& name) {
    return _internalGetShader(name);
}

void ShaderManager::ClearCache() {
    for (auto it = _cache.begin(); it != _cache.end(); it++) {
        delete (it->second);
    }
    _cache.clear();
}
