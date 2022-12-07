//
// Created by patri on 5/25/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_INTERPOLATION_H
#define RHYTHMIC_PROGRAMMING_GAME_INTERPOLATION_H

#include <cmath>
#include "InterpolationType.h"

class Interpolation {
private:

public:
    Interpolation(InterpolationType interpolationType);
    static float In(float progress);
    static float Out(float progress);
    static float InOut(float progress);

    static float Elastic(float progress);

    static float BounceEaseOut(float progress);

    static float Bounce(float progress);
};


#endif //RHYTHMIC_PROGRAMMING_GAME_INTERPOLATION_H
