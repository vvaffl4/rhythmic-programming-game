//
// Created by michelle on 01/06/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_SHADERMANAGER_H
#define RHYTHMIC_PROGRAMMING_GAME_SHADERMANAGER_H

#include <map>
#include <string>
#include "Shader.h"
#include "ShaderSource.h"

class ShaderManager {
private:
    std::map<std::string, Shader*> _cache;
    AAssetManager* _assetManager = nullptr;

    ShaderManager() {};

    Shader* _internalGetShader(std::string& name);

public:
    ShaderManager(ShaderManager const&) = delete;

    void operator=(ShaderManager const&) = delete;

    static ShaderManager& GetInstance() {
        static ShaderManager instance;
        return instance;
    }

    void UseShader(std::string name);

    void SetAssetManager(AAssetManager* assetManager);

    Shader* GetShader(std::string& name);

    void ClearCache();
};


#endif //RHYTHMIC_PROGRAMMING_GAME_SHADERMANAGER_H
