//
// Created by michelle on 17/05/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_SPRITESTRING_H
#define RHYTHMIC_PROGRAMMING_GAME_SPRITESTRING_H

#include <string>
#include <algorithm>
#include "SpritesheetFontFactory.h"
#include "../services/ServiceManager.h"
#include "../render/Scene2D.h"
#include "StringRenderData.cpp"

class SpriteString {
private:
    SpritesheetFont* _font = nullptr;
    Scene2D* _scene = nullptr;
    std::vector<Sprite*> _sprites;

    float _height = -0.000001f;
public:

    SpriteString(AAssetManager* assetManager, std::string font, std::string str);

    ~SpriteString();

    void RenderAdd(Scene2D* scene);

    void RenderRemove(Scene2D* serviceManager);

    void SetPosition(int x, int y, StringAlignment alignment, float scale);

    void SetRotation(float rotation);

    void ScaleSprites(const float scale);

    float GetHeight() { return _height; };
};


#endif //RHYTHMIC_PROGRAMMING_GAME_SPRITESTRING_H
