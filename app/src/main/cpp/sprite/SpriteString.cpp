//
// Created by michelle on 17/05/18.
//

#include "SpriteString.h"

SpriteString::SpriteString(AAssetManager* assetManager, std::string font, std::string str) {
    _font = SpritesheetFontFactory::GetInstance().Load(assetManager, font);
    _sprites = _font->StringToSprites(str);
}

void SpriteString::RenderAdd(Scene2D* scene) {
    _scene = scene;

    for (auto it = _sprites.begin(); it != _sprites.end(); it++) {
        scene->AddModel(*it);
    }
}

void SpriteString::RenderRemove(Scene2D* scene) {
    for (auto it = _sprites.begin(); it != _sprites.end(); it++) {
        scene->RemoveModel(*it);
        delete *it;
    }

    _sprites.clear();
}

SpriteString::~SpriteString() {
    if (_scene != nullptr) RenderRemove(_scene);
}

void SpriteString::SetPosition(int x, int y, StringAlignment alignment, float scale) {
    if (_sprites.size() <= 0)
        return;
    int width = 0;

    float maxHeight = 0.0f;
    for (auto it = _sprites.begin(); it != _sprites.end(); it++) {
        width += ((*it)->GetWidth() * scale);
        maxHeight = std::max(maxHeight, (*it)->GetHeight() * scale);
    }

    _height = maxHeight;

    Sprite* previousSprite = _sprites[0];
    int xPrevious = x;

    switch (alignment) {
        case ALIGN_LEFT: {
            for (auto it = _sprites.begin(); it != _sprites.end(); it++) {
                (*it)->SetPosition(
                        (float) xPrevious,
                        (float) y, 0.0f);
                previousSprite = *it;
                xPrevious += (float) (previousSprite->GetWidth() * scale) * 1;
            }
        }
            break;
        case ALIGN_RIGHT: {
            for (auto it = _sprites.rbegin(); it != _sprites.rend(); it++) {
                (*it)->SetPosition(
                        (float) xPrevious,
                        (float) y, 0.0f);
                previousSprite = *it;
                xPrevious -= (float) (previousSprite->GetWidth() * scale) * 1;
            }
        }
            break;
        case ALIGN_CENTER: {
            for (auto it = _sprites.begin(); it != _sprites.end(); it++) {
                (*it)->SetPosition(
                        (float) (xPrevious - (width / 2)),
                        (float) y, 0.0f);
                previousSprite = *it;
                xPrevious += (float) (previousSprite->GetWidth() * scale) * 1;
            }
        }
            break;
    }

}

void SpriteString::SetRotation(float rotation) {
    for (auto it = _sprites.begin(); it != _sprites.end(); it++) {
        (*it)->SetRotation(glm::angleAxis(glm::radians(rotation), glm::vec3(0, 0, 1)));
    }
}

void SpriteString::ScaleSprites(const float scale) {
    for (auto it = _sprites.begin(); it != _sprites.end(); it++) {
        (*it)->SetScale((float) (*it)->GetWidth() * scale,
                        (float) (*it)->GetHeight() * scale, 0.0f);
    }
}
