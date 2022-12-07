//
// Created by jaron on 5-6-2018.
//

#ifndef REPO_LEADERBOARDBUTTON_H
#define REPO_LEADERBOARDBUTTON_H

#include "../uiobjects/TexturedButton.h"

class LeaderboardButton : public TexturedButton {
private:
    std::string _levelName = "test-level";
public:
    LeaderboardButton(AAssetManager* assetManager, short x, short y);

    void OnButtonUp() override;

    void OnButtonDown() override;

    void SetLevelName(std::string levelName);

    void ClearLevel();
};


#endif //REPO_LEADERBOARDBUTTON_H
