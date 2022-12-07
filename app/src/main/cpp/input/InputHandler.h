//
// Created by patrick on 4/19/2018.
// Reviewed and edited by maarten on 4/23/2018.
//

#ifndef RHYTHMICPROGRAMMING_INPUTHANDLER_H
#define RHYTHMICPROGRAMMING_INPUTHANDLER_H

#include <array>
#include <vector>
#include <android/input.h>
#include <android/native_window.h>
#include "../glm/vec2.hpp"
#include "../System.h"
#include "../services/ServiceManager.h"
#include "../properties.h"

enum InputType {
    DOWN,
    UP,
    MOVE,
};

struct Input {
    unsigned int index;
    InputType type;
    glm::vec2 position;
    glm::vec2 offset;
};

class InputHandler {
private:
    float _screenWidth;
    float _screenHeight;
public:
    InputHandler();

    bool Handle(AInputEvent* event);

    void UseDimensions(int width, int height);
};


#endif //RHYTHMICPROGRAMMING_INPUTHANDLER_H
