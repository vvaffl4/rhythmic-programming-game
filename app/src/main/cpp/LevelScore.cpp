//
// Created by michelle on 31/05/18.
//

#ifndef LEVELSCORE_CPP
#define LEVELSCORE_CPP

#include <map>
#include <string>
#include "input/HitType.cpp"

struct LevelScore {
    std::string level;
    std::map<HitType, int> amounts;
    int combo;
    int comboScore;
    int highestCombo;
    float multiplier = 1.0f;
    int score;
    float accuracy = 1.0f;
    int highscore;
    int placement;
    int hits = 0;
};

#endif