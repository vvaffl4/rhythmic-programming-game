//
// Created by pw on 21-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_UISERVICE_H
#define RHYTHMICPROGRAMMING_UISERVICE_H

class UIObject;

class UIScene;

#include <pthread.h>
#include <algorithm>
#include <vector>
#include "../uiobjects/UIObject.h"
#include "../input/InputHandler.h"
#include "../AudioPlayer.h"
#include "../screens/UIScene.h"

class UIService : public Service {
private:
    System* _system = nullptr;

    UIScene* _scene = nullptr;

    UIScene* _nextScene = nullptr;

    bool _sceneSwitched = false;
public:
    UIService();

    void ProcessInput(Input* input);

private:
    void Listener(Message* message) override;

    void SetScene(UIScene* scene);

    void SwitchScreen();
};


#endif //RHYTHMICPROGRAMMING_UISERVICE_H
