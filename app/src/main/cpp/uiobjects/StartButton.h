//
// Created by pw on 14-5-2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_STARTBUTTON_H
#define RHYTHMIC_PROGRAMMING_GAME_STARTBUTTON_H

#include "UIButton.h"
#include "../MainGame.h"
#include "../screens/LevelSelectionScreen.h"

class StartButton : public UIButton {

public:
    StartButton(short x, short y);

    void OnButtonUp() override;

    void OnButtonDown() override;
};


#endif //RHYTHMIC_PROGRAMMING_GAME_STARTBUTTON_H
