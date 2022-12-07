//
// Created by patri on 4/20/2018.
//

#include "UIObject.h"
#include "../properties.h"

const float UIObject::CENTER = 0.5f;

UIObject::UIObject(short x, short y, short width, short height) :
        _x(x),
        _y(y),
        _width(width),
        _height(height),
        _horizontalAlign(0.0f),
        _verticalAlign(0.0f) {
    _sprite = new Sprite(nullptr);
    _sprite->Translate(glm::vec3(
            x - (width * _horizontalAlign),
            y - (height * _verticalAlign),
            0));
    _sprite->SetScale(
            width,
            height,
            1.0f);
}

UIObject::UIObject(short x, short y, short width, short height, Sprite* sprite) :
        _x(x),
        _y(y),
        _width(width),
        _height(height),
        _horizontalAlign(0.0f),
        _verticalAlign(0.0f),
        _sprite(sprite) {
    _sprite->Translate(glm::vec3(
            x - (width * _horizontalAlign),
            y - (height * _verticalAlign),
            0));
    _sprite->SetScale(
            width,
            height,
            1.0f);
}

UIObject::~UIObject() {
    if (_sprite != nullptr) {
        delete _sprite;
        _sprite = nullptr;
    }
}

void UIObject::SetY(short y) {
    _y = y;

    if (_sprite != nullptr)
        _sprite->SetPosition(glm::vec3(
                _x - (_width * _horizontalAlign),
                _y - (_height * _verticalAlign), 0));
}

Sprite* UIObject::GetSprite() {
    return _sprite;
}

void UIObject::SetAlign(float x, float y) {
    _sprite->Translate(
            (_width * _horizontalAlign),
            (_height * _verticalAlign),
            0);

    _horizontalAlign = x;
    _verticalAlign = y;

    _sprite->Translate(
            -(_width * _horizontalAlign),
            -(_height * _verticalAlign),
            0);
}

void UIObject::SetPosition(short x, short y) {
    _x = x;
    _y = y;
    _sprite->SetPosition(x, y, 0);
}

bool UIObject::_intersectsLine(short x1, short y1, short x2, short y2) {
    return (x1 >= _x - (_width * _horizontalAlign) &&
            x1 <= _x - (_width * _horizontalAlign) + _width &&
            y1 >= _y - (_height * _verticalAlign) &&
            y1 <= _y - (_height * _verticalAlign) + _height) ||
           (x2 >= _x - (_width * _horizontalAlign) &&
            x2 <= _x - (_width * _horizontalAlign) + _width &&
            y2 >= _y - (_height * _verticalAlign) &&
            y2 <= _y - (_height * _verticalAlign) + _height);
}

short UIObject::GetY() {
    return _y;
}

void UIObject::SetXFromRight(short offset) {
    SetX(static_cast<short>(Properties.WIDTH - (offset + _width)));
}

void UIObject::SetYFromBottom(short offset) {
    SetY(static_cast<short>(Properties.HEIGHT - (offset + _height)));
}

short UIObject::GetWidth() {
    return _width;
}

void UIObject::CenterHorizontally() {
    SetX(static_cast<short>((Properties.WIDTH / 2) - (_width / 2)));
}

bool UIObject::IsVisible() {
    return _visible;
}

void UIObject::SetVisible(bool b) {
    _visible = b;
}

void UIObject::SetX(short x) {
    _x = x;
}
