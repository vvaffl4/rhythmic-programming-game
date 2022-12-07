//
// Created by michelle on 16/05/18.
//

#include "SpritesheetFontFactory.h"

SpritesheetFont* SpritesheetFontFactory::Load(AAssetManager* assetManager, std::string path) {
    if (_cache[path]) {
        return _cache[path];
    }

    INIReader reader(assetManager, path);
    std::string spritesheetPath = reader.Get("general", "spritesheet", "");
    Spritesheet* spritesheet = SpritesheetFactory::GetInstance().Load(assetManager,
                                                                      spritesheetPath.c_str());

    SpritesheetFont* font = new SpritesheetFont(spritesheet);
    std::vector<std::string> sections = reader.Sections();
    for (auto it = sections.begin(); it != sections.end(); it++) {
        if ((*it) != "general") {
            font->AddLetter(*it, reader.Get(*it, "sprite", ""));
        }
    }

    _cache[path] = font;
    return font;
}

void SpritesheetFontFactory::ClearCache() {
    for (auto it = _cache.begin(); it != _cache.end(); it++) {
        delete (it->second);
    }
    _cache.clear();
    SpritesheetFactory::GetInstance().ClearCache();
}
