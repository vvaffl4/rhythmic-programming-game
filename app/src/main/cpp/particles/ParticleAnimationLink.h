//
// Created by patri on 5/31/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_PARTICLEANIMATIONLINK_H
#define RHYTHMIC_PROGRAMMING_GAME_PARTICLEANIMATIONLINK_H

class ParticleAnimation;

#include <vector>
#include "ParticleAnimation.h"
#include "ParticleProperties.h"
#include "Particle.h"

struct ParticleAnimationLink{
    ParticleAnimation* particleAnimation;
    std::vector<Particle*> animationParticles;
    ParticleProperties customParticleProperties;
    unsigned int particleIndex;
    unsigned long start;                        //AudioStart Position
    bool isCustom;
    bool isDone;                                //IsDone - for removal
};

#endif //RHYTHMIC_PROGRAMMING_GAME_PARTICLEANIMATIONLINK_H
