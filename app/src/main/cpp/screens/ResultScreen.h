//
// Created by Anne on 16-5-2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_RESULTSCREEN_H
#define RHYTHMIC_PROGRAMMING_GAME_RESULTSCREEN_H

#include "../services/ServiceManager.h"
#include "../services/UIService.h"
#include "../input/InputHandler.h"
#include "UIScene.h"
#include "../properties.h"
#include "../services/LogicService.h"
#include "../ResourceManager.h"
#include "../uiobjects/StartButton.h"
#include "../uiobjects/MainMenuButton.h"
#include "../uiobjects/ReplayButton.h"
#include "../LevelScore.cpp"

class ResultScreen : public UIScene {

private:
    LevelScore* _levelScore = nullptr;

    void _sendScoreMessage();

    void _sendHitScoreMessage();

    void _sendComboScoreMessage();

    void _sendAccuracyScoreMessage();

    void _sendHighscoreScoreMessage();

    void _initializeResources(AAssetManager* assetManager, ResourceManager& resourceManager);

public :
    ResultScreen(short x, short y, LevelScore* levelScore);

    void Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) override;

    void Release() override;
};


#endif //RHYTHMIC_PROGRAMMING_GAME_RESULTSCREEN_H
