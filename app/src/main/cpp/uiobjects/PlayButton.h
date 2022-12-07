//
// Created by michelle on 08/06/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_PLAYBUTTON_H
#define RHYTHMIC_PROGRAMMING_GAME_PLAYBUTTON_H


#include "TexturedButton.h"

class PlayButton : public TexturedButton {
private:
    bool _hasLevel = false;
    std::string _level;
public:
    PlayButton(AAssetManager* assetManager, short x, short y);

    ~PlayButton() override;

    void OnButtonDown() override;

    void OnButtonUp() override;

    void SetLevel(std::string level);

    void ClearLevel();
};


#endif //RHYTHMIC_PROGRAMMING_GAME_PLAYBUTTON_H
