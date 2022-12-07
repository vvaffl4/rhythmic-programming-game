//
// Created by jaron on 5-6-2018.
//

#include "UIScene.h"
#include "../sprite/StringRenderData.cpp"
#include "../ResourceManager.h"
#include "../HighscoreFactory.h"

#ifndef REPO_LEADERBOARD_H
#define REPO_LEADERBOARD_H

#include "../uiobjects/MainMenuButton.h"
#include "../uiobjects/LevelSelectionButton.h"

class Leaderboard : public UIScene {
private:
    std::string _levelName;
    LevelSelectionButton* _levelSelectionButton = nullptr;

    void _sendLeaderboardMessage(ANativeActivity* nativeActivity);
    void _initializeResources(AAssetManager* assetManager, ResourceManager& resourceManager);

public:
    Leaderboard(int x, int y, std::string levelName);

    void Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) override;

    void Release() override;
};


#endif //REPO_LEADERBOARD_H
