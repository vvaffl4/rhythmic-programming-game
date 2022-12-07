//
// Created by michelle on 19/04/18.
//

#ifndef RYTHMIC_PROGRAMMING_LEVEL_H
#define RYTHMIC_PROGRAMMING_LEVEL_H

#include <cstdint>
#include "LevelStructs.cpp"

#endif //RYTHMIC_PROGRAMMING_LEVEL_H

#ifndef RYTHMIC_PROGRAMMING_LEVELFACTORY_H
#define RYTHMIC_PROGRAMMING_LEVELFACTORY_H

#ifndef LEVELFACTORY_STRUCTS_ONLY

#include <string>
#include <map>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class LevelFactory {
private:
    std::map<const char*, Level*> _cache;

    LevelFactory() {}

public:
    LevelFactory(LevelFactory const&) = delete;

    void operator=(LevelFactory const&) = delete;

    static LevelFactory& GetInstance() {
        static LevelFactory instance;
        return instance;
    }

    Level* Load(AAssetManager*, const std::string&);
};


#endif //RYTHMIC_PROGRAMMING_LEVELFACTORY_H
#endif