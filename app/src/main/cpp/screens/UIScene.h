//
// Created by patri on 5/15/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_UISCENE_H
#define RHYTHMIC_PROGRAMMING_GAME_UISCENE_H

#include <android/asset_manager.h>
#include "../uiobjects/UIObject.h"

class UIScene : public UIObject {
protected:
    std::vector<UIObject*> _objects;
public:
    UIScene(short x, short y, short width, short height);

    virtual ~UIScene();

    virtual void Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) = 0;

    virtual void Release() = 0;

    virtual void Update(double d) {};

    virtual void ProcessInput(Input* input) override;
};


#endif //RHYTHMIC_PROGRAMMING_GAME_UISCENE_H
