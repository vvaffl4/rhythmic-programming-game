//
// Created by michelle on 13/06/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_LEVELSELECTIONBUTTON_H
#define RHYTHMIC_PROGRAMMING_GAME_LEVELSELECTIONBUTTON_H

#include "TexturedButton.h"

class LevelSelectionButton : public TexturedButton {
public:
    LevelSelectionButton(AAssetManager* assetManager, short x, short y);

    void OnButtonUp() override;

    void OnButtonDown() override;
};


#endif //RHYTHMIC_PROGRAMMING_GAME_LEVELSELECTIONBUTTON_H
