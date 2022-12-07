//
// Created by patri on 4/20/2018.
//

#ifndef RHYTHMICPROGRAMMING_UIOBJECT_H
#define RHYTHMICPROGRAMMING_UIOBJECT_H

class UIService;

#include "../input/InputHandler.h"
#include "../sprite/Sprite.h"
#include "../properties.h"

class UIObject {
protected:
    UIObject(short x, short y, short width, short height, Sprite* sprite);

    short _x;
    short _y;
    short _width;
    short _height;

    float _horizontalAlign = 0.0f;
    float _verticalAlign = 0.0f;
    bool _visible = true;

    Sprite* _sprite = nullptr;

    bool _intersectsLine(short x1, short y1, short x2, short y2);


public:
    UIObject(short x, short y, short width, short height);

    virtual ~UIObject();

    virtual void ProcessInput(Input* input) = 0;

    Sprite* GetSprite();

    virtual void SetX(short x);

    void SetXFromRight(short offset);

    void CenterHorizontally();

    virtual void SetY(short y);

    void SetYFromBottom(short offset);

    short GetY();

    virtual short GetWidth();

    void SetAlign(float x, float y);

    void SetPosition(short x, short y);

    virtual bool IsVisible();

    virtual void SetVisible(bool b);

    static const float CENTER;
};


#endif //RHYTHMICPROGRAMMING_UIOBJECT_H
