//
// Created by Anne on 25-5-2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_TAPBEAT_H
#define RHYTHMIC_PROGRAMMING_GAME_TAPBEAT_H


#include "ScreenBeat.h"

class TapBeat : public ScreenBeat {
protected:
    void _initializeBeat() override;

public:
    TapBeat(Beat beat, LaneSide laneSide, short targetX, short targetY);

    float GetBeatEnd() override;

    void Update(float audioPosition) override;

    void ClearBeat() override;
};


#endif //RHYTHMIC_PROGRAMMING_GAME_TAPBEAT_H
