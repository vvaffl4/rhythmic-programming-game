//
// Created by patri on 5/25/2018.
//

#include "Interpolation.h"

Interpolation::Interpolation(InterpolationType interpolationType) {}

float Interpolation::In(float progress) {
    return progress * progress * progress;
}

float Interpolation::Out(float progress) {
    return (--progress) * progress * progress + 1;
}

float Interpolation::InOut(float progress) {
    return progress < .5 ? 4 * progress * progress * progress :
           (progress - 1) * (2 * progress - 2) * (2 * progress - 2) + 1;
}

float Interpolation::Elastic(float progress) {
    float p = 0.3f;
    return static_cast<float>(pow(2.0f, -10.0f * progress) * sin((progress - p / 4.0f) * (2 * M_PI) / p) + 1);
}

float  Interpolation::BounceEaseOut(float progress) {

    if(progress < 4/11.0)
    {
        return static_cast<float>((121 * progress * progress) / 16.0);
    }
    else if(progress < 8/11.0)
    {
        return static_cast<float>((363 / 40.0 * progress * progress) - (99 / 10.0 * progress) + 17 / 5.0);
    }
    else if(progress < 9/10.0)
    {
        return static_cast<float>((4356 / 361.0 * progress * progress) - (35442 / 1805.0 * progress) + 16061 / 1805.0);
    }
    else
    {
        return static_cast<float>((54 / 5.0 * progress * progress) - (513 / 25.0 * progress) + 268 / 25.0);
    }
}

float Interpolation::Bounce(float progress) {

    if(progress < 0.5)
    {
        return static_cast<float>(0.5 * 1 - BounceEaseOut(1 - progress));
    }
    else
    {
        return static_cast<float>(0.5 * BounceEaseOut(progress * 2 - 1) + 0.5);
    }
}