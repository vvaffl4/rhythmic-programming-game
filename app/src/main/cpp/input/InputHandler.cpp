//
// Created by patrick on 4/19/2018.
// Reviewed and edited by maarten on 4/23/2018.
//

#include "InputHandler.h"

InputHandler::InputHandler() {}

void InputHandler::UseDimensions(int width, int height) {
    _screenWidth = width;
    _screenHeight = height;
}

bool InputHandler::Handle(AInputEvent* event) {
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {

        int32_t pointerAction = AMotionEvent_getAction(event);
        int32_t pointerIndex = (pointerAction & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
                >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

        float pointerX = AMotionEvent_getX(event, pointerIndex) / _screenWidth * Properties.WIDTH;
        float pointerY = AMotionEvent_getY(event, pointerIndex) / _screenHeight * Properties.HEIGHT;

        Input* input = new Input();
        input->index = static_cast<unsigned int>(pointerIndex);
        input->position = glm::vec2(pointerX, pointerY);
        input->offset = glm::vec2(0.0f, 0.0f);

        if (pointerAction == AMOTION_EVENT_ACTION_MOVE) {
            input->type = MOVE;
        } else {
            if ((pointerAction % 256) == AMOTION_EVENT_ACTION_UP ||
                (pointerAction % 256) == AMOTION_EVENT_ACTION_POINTER_UP) {
                input->type = UP;
            } else {
                input->type = DOWN;
            }
        }

        ServiceManager::GetInstance().Send(new Message{
                MessageType::INPUT,
                input
        });

        return true;
    }

    return false;
}

