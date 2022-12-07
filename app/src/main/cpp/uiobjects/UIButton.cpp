//
// Created by pw on 21-4-2018.
//

#include "UIButton.h"

UIButton::UIButton(short x, short y, short width, short height) :
        UIObject(x, y, width, height) {}

UIButton::~UIButton() {

}

void UIButton::ProcessInput(Input* input) {
    if (_intersectsLine(
            static_cast<short>(input->position.x),
            static_cast<short>(input->position.y),
            static_cast<short>(input->position.x - input->offset.x),
            static_cast<short>(input->position.y - input->offset.y))) {
        switch (input->type) {
            case UP:
                _buttonState = BUTTON_UP;
                OnButtonUp();
                break;
            case DOWN:
                _buttonState = BUTTON_DOWN;
                OnButtonDown();
                break;
            case MOVE:
                break;
        }
    }
}
