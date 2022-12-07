//
// Created by patri on 5/25/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_PARTICLEANIMATION_H
#define RHYTHMIC_PROGRAMMING_GAME_PARTICLEANIMATION_H

#include <vector>
#include "ParticleAnimationLink.h"
#include "Particle.h"
#include "ParticleTemplate.h"
#include "ParticleProperties.h"

class ParticleAnimation {
private:
    std::vector<ParticleTemplate*> _particleTemplates;

    void _addProximityParticle(ParticleAnimationLink* particleAnimationLink,
                               unsigned long milliSeconds);

    void _removeProximityParticles(ParticleAnimationLink* particleAnimationLink,
                                   unsigned long milliSeconds);

    void _updateProximityParticles(ParticleAnimationLink* particleAnimationLink,
                                   unsigned long milliSeconds);

public:
    ParticleAnimation();

    ~ParticleAnimation();

    void QueueParticle(ParticleTemplate* particle);

    void Update(ParticleAnimationLink* particleAnimationLink, unsigned long milliSeconds);

};


#endif //RHYTHMIC_PROGRAMMING_GAME_PARTICLEANIMATION_H
