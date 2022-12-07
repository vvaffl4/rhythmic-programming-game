//
// Created by Anne on 23-4-2018.
//


#include "HitHandler.h"

HitHandler::HitHandler() {}

HitType HitHandler::Handle(float position, float beatPosition) {
    if (beatPosition == 0) return HitType::NO_BEAT;

    return _calculateScore(abs(position - floor(beatPosition)));
}

HitType HitHandler::_calculateScore(float difference) {
    if (difference < MAX_DISTANCE * PERFECT_THRESHOLD) return HitType::PERFECT;
    if (difference < MAX_DISTANCE * GREAT_THRESHOLD) return HitType::GREAT;
    if (difference < MAX_DISTANCE * GOOD_THRESHOLD) return HitType::GOOD;
    if (difference < MAX_DISTANCE * BAD_THRESHOLD) return HitType::BAD;

    return HitType::MISS;
}