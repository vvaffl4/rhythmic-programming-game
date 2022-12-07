//
// Created by Anne on 16-5-2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_MAINMENUBUTTON_H
#define RHYTHMIC_PROGRAMMING_GAME_MAINMENUBUTTON_H

#include "UIButton.h"

class MainMenuButton : public UIButton {
public:
    MainMenuButton(short x, short y);

    void OnButtonUp() override;

    void OnButtonDown() override;
};


#endif //RHYTHMIC_PROGRAMMING_GAME_MAINMENUBUTTON_H
