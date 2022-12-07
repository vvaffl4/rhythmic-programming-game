//
// Created by pw on 15-5-2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_SYSTEM_H
#define RHYTHMIC_PROGRAMMING_GAME_SYSTEM_H

#include <android/asset_manager.h>
#include <android/native_window.h>
#include <android/native_activity.h>

struct System {
    ANativeWindow* nativeWindow;
    AAssetManager* assetManager;
    ANativeActivity* nativeActivity;
};

#endif //RHYTHMIC_PROGRAMMING_GAME_SYSTEM_H
