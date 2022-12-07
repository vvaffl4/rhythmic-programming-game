//
// Created by michelle on 01/06/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_SHADERSOURCE_H
#define RHYTHMIC_PROGRAMMING_GAME_SHADERSOURCE_H

#include <string>
#include <android/asset_manager.h>
#include "Shader.h"

class ShaderSource {
private:
    Shader* _shader = nullptr;
    std::string _name;
    std::string _vshSource;
    std::string _fshSource;
    int _status = 0;
    bool _deleteShader = true;

    void _loadSources(AAssetManager* assetManager);

public:
    ShaderSource() {};

    ~ShaderSource();

    ShaderSource(AAssetManager* assetManager, std::string name);

    Shader* GetShader();

    void KeepShader();
};


#endif //RHYTHMIC_PROGRAMMING_GAME_SHADERSOURCE_H
