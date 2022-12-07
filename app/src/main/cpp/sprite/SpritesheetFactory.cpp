//
// Created by michelle on 09/05/18.
//

#include "SpritesheetFactory.h"

Spritesheet* SpritesheetFactory::Load(AAssetManager* assetManager, const char* path) {
    if (SpritesheetFactory::_cache[path]) {
        return SpritesheetFactory::_cache[path];
    }

    INIReader reader(assetManager, path);
    std::string g = reader.Get("general", "user", "default");

    std::string spritefile = reader.Get("general", "file", "");
    std::string mode = reader.Get("General", "mode", "quad");

    Spritesheet* spritesheet = new Spritesheet(assetManager, spritefile);

    std::vector<std::string> sections = reader.Sections();
    for (auto it = sections.begin(); it != sections.end(); it++) {
        if (*it != "general") {
            int x = (int) reader.GetInteger(*it, "x", 0);
            int y = (int) reader.GetInteger(*it, "y", 0);
            int w = (int) reader.GetInteger(*it, "w", 0);
            int h = (int) reader.GetInteger(*it, "h", 0);

            spritesheet->AddSprite(*it, x, y, w, h);
        }
    }

    SpritesheetFactory::_cache[path] = spritesheet;
    return spritesheet;
}

void SpritesheetFactory::ClearCache() {
    for (auto it = _cache.begin(); it != _cache.end(); it++) {
        delete (it->second);
    }
    _cache.clear();
}
