//
// Created by michelle on 15/05/18.
//

#include "SpriteDefinition.h"

SpriteDefinition::SpriteDefinition(std::string name, int x, int y, int w, int h) :
        _name(name),
        _x(x),
        _y(y),
        _width(w),
        _height(h) {}

SpriteDefinition::~SpriteDefinition() {
    if (_sprite != nullptr) {
        delete _sprite;
        _sprite = nullptr;
    }
}

std::string SpriteDefinition::GetName() {
    return _name;
}

Sprite* SpriteDefinition::CreateSprite(Texture* texture, int textureWidth, int textureHeight) {
    if (_sprite != nullptr) {
        return _sprite;
    }

    float spx = (float) _x / (float) textureWidth;
    float spy = (float) _y / (float) textureHeight;
    float ssw = (float) _width / (float) textureWidth;
    float ssh = (float) _height / (float) textureHeight;

    GLfloat vertices[] = {
            // Pos      // Tex
            0.0f, 1.0f, spx, spy + ssh,
            1.0f, 0.0f, spx + ssw, spy,
            0.0f, 0.0f, spx, spy,

            0.0f, 1.0f, spx, spy + ssh,
            1.0f, 1.0f, spx + ssw, spy + ssh,
            1.0f, 0.0f, spx + ssw, spy
    };

    Sprite* sprite = new Sprite(texture, vertices);

    sprite->SetDimensions(_width, _height);

    return sprite;
}
