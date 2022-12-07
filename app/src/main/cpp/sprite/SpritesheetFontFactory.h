//
// Created by michelle on 16/05/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_SPRITESHEETFONTFACTORY_H
#define RHYTHMIC_PROGRAMMING_GAME_SPRITESHEETFONTFACTORY_H

#include <map>
#include <string>
#include <android/asset_manager.h>
#include "../INIReader.h"
#include "Spritesheet.h"
#include "SpritesheetFont.h"
#include "SpritesheetFactory.h"

class SpritesheetFontFactory {
private:
    std::map<std::string, SpritesheetFont*> _cache;

    SpritesheetFontFactory() {}

public:
    SpritesheetFontFactory(SpritesheetFontFactory const&) = delete;

    void operator=(SpritesheetFontFactory const&) = delete;

    static SpritesheetFontFactory& GetInstance() {
        static SpritesheetFontFactory instance;
        return instance;
    }

    SpritesheetFont* Load(AAssetManager* assetManager, std::string);

    void ClearCache();
};


#endif //RHYTHMIC_PROGRAMMING_GAME_SPRITESHEETFONTFACTORY_H
