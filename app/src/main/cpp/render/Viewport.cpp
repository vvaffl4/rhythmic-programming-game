//
// Created by patri on 4/20/2018.
//

#include "Viewport.h"

Viewport::Viewport(short x, short y, short width, short height) :
        _x(x),
        _y(y),
        _width(width),
        _height(height) {}

void Viewport::use() {
    glViewport(_x, _y, _width, _height);
}
