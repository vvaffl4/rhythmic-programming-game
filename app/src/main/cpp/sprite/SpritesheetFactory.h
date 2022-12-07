//
// Created by michelle on 09/05/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_SPRITESHEETFACTORY_H
#define RHYTHMIC_PROGRAMMING_GAME_SPRITESHEETFACTORY_H


#include "Spritesheet.h"
#include <map>
#include <android/asset_manager.h>
#include "../INIReader.h"
#include <android/log.h>

class SpritesheetFactory {
private:
    std::map<const char*, Spritesheet*> _cache;

    SpritesheetFactory() {};

public:
    SpritesheetFactory(SpritesheetFactory const&) = delete;

    void operator=(SpritesheetFactory const&) = delete;

    static SpritesheetFactory& GetInstance() {
        static SpritesheetFactory instance;
        return instance;
    }

    Spritesheet* Load(AAssetManager*, const char*);

    void ClearCache();
};


#endif //RHYTHMIC_PROGRAMMING_GAME_SPRITESHEETFACTORY_H
