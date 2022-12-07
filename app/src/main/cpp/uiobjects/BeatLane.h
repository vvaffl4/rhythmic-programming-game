//
// Created by pw on 22-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_TESTLANE_H
#define RHYTHMICPROGRAMMING_TESTLANE_H

#include "UIObject.h"
#include "../services/UIService.h"
#include "../ResourceManager.h"

class BeatLane : public UIObject {
public:
    BeatLane();

    void SetTexture(Texture* texture);

    void ProcessInput(Input* input) override;
};


#endif //RHYTHMICPROGRAMMING_TESTLANE_H
