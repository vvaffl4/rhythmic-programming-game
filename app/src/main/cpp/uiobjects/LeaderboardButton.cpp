//
// Created by jaron on 5-6-2018.
//

#include "LeaderboardButton.h"
#include "../screens/Leaderboard.h" // Include lives here to prevent circular include

LeaderboardButton::LeaderboardButton(AAssetManager* assetManager, short x, short y)
        : TexturedButton(assetManager, "main_menu_leaderboard.png", x, y, 280, 180) {

}

void LeaderboardButton::OnButtonUp() {

}

void LeaderboardButton::OnButtonDown() {
    ServiceManager::GetInstance().Send(new Message{
            UNRENDER_ALL_STRINGS,
            NULL
    });

    ServiceManager::GetInstance().Send(new Message{
            SET_UISCENE,
            new Leaderboard(0, 0, _levelName)
    });
}

void LeaderboardButton::SetLevelName(std::string levelName) {
    _levelName = "levels/";
    _levelName += levelName;
}

void LeaderboardButton::ClearLevel() {
    _levelName = "test-level";
}
