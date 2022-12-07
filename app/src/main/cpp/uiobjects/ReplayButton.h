//
// Created by jaron on 24-5-2018.
//

#ifndef REPO_REPLAYBUTTON_H
#define REPO_REPLAYBUTTON_H


#include "UIButton.h"
#include "../MainGame.h"

class ReplayButton : public UIButton {
private:
    bool _hasLevel = false;
    std::string _level;
public:
    ReplayButton(short x, short y);

    void OnButtonUp() override;

    void OnButtonDown() override;

    void SetLevel(std::string level);
};


#endif //REPO_REPLAYBUTTON_H
