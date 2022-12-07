//
// Created by patri on 6/6/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_TITLESCREEN_H
#define RHYTHMIC_PROGRAMMING_GAME_TITLESCREEN_H

#include "UIScene.h"
#include "../ResourceManager.h"
#include "../uiobjects/UIImage.h"

class TitleScreen : public UIScene {
private:
    void _initializeResources(AAssetManager* assetManager, ResourceManager& resourceManager);

public:
    TitleScreen(short x, short y);

    void Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) override;

    void Release() override;

    void ProcessInput(Input* input) override;
};


#endif //RHYTHMIC_PROGRAMMING_GAME_TITLESCREEN_H
