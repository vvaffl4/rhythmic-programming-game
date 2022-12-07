//
// Created by patri on 5/24/2018.
//

#include "WorkspaceObject.h"

WorkspaceObject::WorkspaceObject() :
        _x(0),
        _y(0),
        _width(0),
        _height(0),
        _horizontalAlign(0.0f),
        _verticalAlign(0.0f) {}

WorkspaceObject::WorkspaceObject(short x, short y, short width, short height) :
        _x(x),
        _y(y),
        _width(width),
        _height(height),
        _horizontalAlign(0.0f),
        _verticalAlign(0.0f) {}


WorkspaceObject::~WorkspaceObject() {}

void WorkspaceObject::SetX(short x) {
    _x = x;
}

void WorkspaceObject::SetY(short y) {
    _y = y;
}

void WorkspaceObject::SetWidth(short width) {
    _width = width;
}

void WorkspaceObject::SetHeight(short height) {
    _height = height;
}

void WorkspaceObject::SetAlign(float x, float y) {
    _horizontalAlign = x;
    _verticalAlign = y;
}

void WorkspaceObject::SetPosition(short x, short y) {
    _x = x;
    _y = y;
}

bool WorkspaceObject::ShouldBeDeleted() {
    return _toBeDeleted;
}
