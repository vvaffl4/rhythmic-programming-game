//
// Created by pw on 15-5-2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_MAINGAME_H
#define RHYTHMIC_PROGRAMMING_GAME_MAINGAME_H

#include "screens/UIScene.h"
#include "properties.h"
#include "ResourceManager.h"
#include "uiobjects/BeatHitDetectionButton.h"
#include "uiobjects/BeatLane.h"

class MainGame : public UIScene {
private:
    void _initializeResources(AAssetManager* assetManager, ResourceManager& resourceManager);

public:
    MainGame(short x, short y);

    void Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) override;

    void Release() override;
};


#endif //RHYTHMIC_PROGRAMMING_GAME_MAINGAME_H
