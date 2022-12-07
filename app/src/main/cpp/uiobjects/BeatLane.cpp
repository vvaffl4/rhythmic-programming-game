//
// Created by pw on 22-4-2018.
//

#include "BeatLane.h"

BeatLane::BeatLane() :
        UIObject(0, 0, static_cast<short>(120), static_cast<short>(450)) {

    _sprite->SetTexture(ResourceManager::GetInstance().GetTexture("main_game_lane"));
}

void BeatLane::SetTexture(Texture* texture) {
    _sprite->SetTexture(texture);
}

void BeatLane::ProcessInput(Input* input) {
    /*
     * Needed for input loop
     */
}
