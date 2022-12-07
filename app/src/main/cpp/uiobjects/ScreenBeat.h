//
// Created by patri on 4/26/2018.
//

#ifndef RHYTHMICPROGRAMMING_TESTBEAT_H
#define RHYTHMICPROGRAMMING_TESTBEAT_H

class LogicService;

#include "UIObject.h"
#include "../services/UIService.h"
#include "../LevelStructs.cpp"
#include "../properties.h"
#include "../LaneSide.h"
#include "../ResourceManager.h"
#include "../input/BeatTypes.h"

class ScreenBeat : public UIObject {
protected:
    Beat _beat;
    LaneSide _laneSide;
    BeatType _beatType;
    short _targetX;
    short _targetY;
    bool _isPressed = false;

    virtual void _initializeBeat();

public:

    ScreenBeat(Beat beat, LaneSide laneSide, short targetX, short targetY, BeatType type);

    void ProcessInput(Input* input) override;

    virtual void Update(float audioPosition);

    void SetTexture(Texture* texture);

    float GetBeatPosition();

    float GetBeatDuration();

    virtual float GetBeatEnd() = 0;

    virtual void ClearBeat() = 0;

    BeatType GetBeatType();

    void SetBeatPressed(bool pressed);

    bool GetBeatPressed();

    LaneSide GetLaneSide();
};


#endif //RHYTHMICPROGRAMMING_TESTBEAT_H
