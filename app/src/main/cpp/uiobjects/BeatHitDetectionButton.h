//
// Created by pw on 22-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_TESTBUTTON_H
#define RHYTHMICPROGRAMMING_TESTBUTTON_H

#include "UIButton.h"
#include "../LaneSide.h"
#include "../ResourceManager.h"

class BeatHitDetectionButton : public UIButton {
private:
    Texture* _upTexture = nullptr;
    Texture* _downTexture = nullptr;
    LaneSide _side;

public:
    BeatHitDetectionButton(LaneSide side);

    void OnButtonUp() override;

    void OnButtonDown() override;

    void SetUpTexture(Texture* texture);

    void SetDownTexture(Texture* texture);
};


#endif //RHYTHMICPROGRAMMING_TESTBUTTON_H
