//
// Created by pw on 21-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_UIBUTTON_H
#define RHYTHMICPROGRAMMING_UIBUTTON_H


#include "UIObject.h"
#include "../services/UIService.h"

enum UIButtonState {
    BUTTON_UP,
    BUTTON_DOWN
};

class UIButton : public UIObject {
protected:
    UIButtonState _buttonState;

public:
    UIButton(short x, short y, short width, short height);

    ~UIButton();

    virtual void OnButtonUp() = 0;

    virtual void OnButtonDown() = 0;

    void ProcessInput(Input* input) override;
};


#endif //RHYTHMICPROGRAMMING_UIBUTTON_H
