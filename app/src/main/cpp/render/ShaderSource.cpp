//
// Created by michelle on 01/06/18.
//

#include "ShaderSource.h"

ShaderSource::ShaderSource(AAssetManager* assetManager, std::string name) : _name(name) {
    _loadSources(assetManager);
}

ShaderSource::~ShaderSource() {
    if (_deleteShader && _shader != nullptr) {
        delete _shader;
        _shader = nullptr;
    }
}

void ShaderSource::_loadSources(AAssetManager* assetManager) {
    std::string vshPath = "shader/";
    std::string fshPath = vshPath + _name + ".frag";
    vshPath += _name + ".vert";

    _status++;
    AAsset* asset = AAssetManager_open(assetManager, vshPath.c_str(), AASSET_MODE_UNKNOWN);
    if (asset == nullptr) return;

    _status++;
    off_t length = AAsset_getLength(asset);
    char* vshBuffer = static_cast<char*>(malloc(static_cast<size_t>(length)));
    AAsset_read(asset, vshBuffer, static_cast<size_t>(length));
    AAsset_close(asset);
    _vshSource = vshBuffer;
    free(vshBuffer);

    asset = AAssetManager_open(assetManager, fshPath.c_str(), AASSET_MODE_UNKNOWN);
    if (asset == nullptr) return;

    _status++;
    length = AAsset_getLength(asset);
    char* fshBuffer = static_cast<char*>(malloc(static_cast<size_t>(length)));
    AAsset_read(asset, fshBuffer, static_cast<size_t>(length));
    AAsset_close(asset);
    _fshSource = fshBuffer;
    free(fshBuffer);

    _status++;
}

Shader* ShaderSource::GetShader() {
    if (_shader != nullptr) {
        return _shader;
    }

    _shader = new Shader(_vshSource, _fshSource);
    return _shader;
}

void ShaderSource::KeepShader() {
    _deleteShader = false;
}
