//
// Created by michelle on 15/05/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_SPRITEDEFINITION_H
#define RHYTHMIC_PROGRAMMING_GAME_SPRITEDEFINITION_H

#include <string>
#include "Sprite.h"
#include "../render/Texture.h"

class SpriteDefinition {
private:
    std::string _name;
    int _x = 0;
    int _y = 0;
    int _width = 0;
    int _height = 0;
    Sprite* _sprite = nullptr;

public:
    SpriteDefinition(std::string name, int x, int y, int w, int h);

    ~SpriteDefinition();

    std::string GetName();

    Sprite* CreateSprite(Texture* texture, int textureWidth, int textureHeight);
};


#endif //RHYTHMIC_PROGRAMMING_GAME_SPRITEDEFINITION_H
