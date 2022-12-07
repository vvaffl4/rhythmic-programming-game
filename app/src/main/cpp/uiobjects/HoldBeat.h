//
// Created by Anne on 25-5-2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_HOLDBEAT_H
#define RHYTHMIC_PROGRAMMING_GAME_HOLDBEAT_H


#include "ScreenBeat.h"
#include "../properties.h"


class HoldBeat : public ScreenBeat {
private:
    Sprite* _spriteDown = nullptr;
    Sprite* _spriteMiddle = nullptr;
    Sprite* _spriteUp = nullptr;
    Sprite* _spriteUpTail = nullptr;
    Sprite* _spriteDownTail = nullptr;

    bool _tailBeat = true;

    void _clearTailBeats();

    void _removeTail();

protected:
    void _initializeBeat() override;

public:

    HoldBeat(Beat beat, LaneSide laneSide, short targetX, short targetY);

    ~HoldBeat();

    void Update(float audioPosition) override;

    void ClearBeat() override;

    float GetBeatEnd() override;
};


#endif //RHYTHMIC_PROGRAMMING_GAME_HOLDBEAT_H