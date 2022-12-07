//
// Created by patri on 5/15/2018.
//

#include "UIScene.h"

UIScene::UIScene(short x, short y, short width, short height) :
        UIObject(x, y, width, height) {}

void UIScene::ProcessInput(Input* input) {

    for (auto it = _objects.begin(); it != _objects.end(); ++it) {
        if (!(*it)->IsVisible()) continue;
        (*it)->ProcessInput(input);
    }
}

UIScene::~UIScene() {

    for (auto it = _objects.begin(); it != _objects.end(); it++) {
        delete *it;
    }

    _objects.clear();
}

