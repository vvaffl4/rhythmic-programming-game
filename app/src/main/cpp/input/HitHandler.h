//
// Created by Anne on 23-4-2018.
//

#ifndef RYTHMIC_PROGRAMMING_HITHANDLER_H
#define RYTHMIC_PROGRAMMING_HITHANDLER_H


#include <math.h>

#include "../LevelFactory.h"
#include "HitType.cpp"

class HitHandler {
protected:
    const float PERFECT_THRESHOLD = 0.12f;
    const float GREAT_THRESHOLD = 0.23f;
    const float GOOD_THRESHOLD = 0.34f;
    const float BAD_THRESHOLD = 0.52f;
    const float MAX_DISTANCE = 300;

public:
    HitHandler();

    HitType _calculateScore(float);

    HitType Handle(float position, float beatPosition);
};

#endif //RYTHMIC_PROGRAMMING_HITHANDLER_H
