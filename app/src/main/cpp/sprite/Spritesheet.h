//
// Created by michelle on 09/05/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_SPRITESHEET_H
#define RHYTHMIC_PROGRAMMING_GAME_SPRITESHEET_H

#include <vector>
#include <string>
#include <android/asset_manager.h>
#include <map>
#include "SpriteDefinition.h"
#include "../render/Texture.h"
#include "Sprite.h"
#include "../ResourceManager.h"
#include "Sprite.h"

class Spritesheet {
private:
    std::string _spritesheetPath;
    std::vector<SpriteDefinition> _sprites;
    std::map<std::string, Sprite*> _spriteCache;

    AAssetManager* _assetManager = nullptr;
    Texture* _texture = nullptr;
    int _textureWidth = 0;
    int _textureHeight = 0;

    void _loadTexture();

public:
    Spritesheet(AAssetManager* spritesheetPath, std::string string);

    ~Spritesheet();

    void AddSprite(std::string, int x, int y, int w, int h);

    Sprite* Get(std::string name);

    Sprite* Get(std::string name, bool skipCache);
};


#endif //RHYTHMIC_PROGRAMMING_GAME_SPRITESHEET_H
