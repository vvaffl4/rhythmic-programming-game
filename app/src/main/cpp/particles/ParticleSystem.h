//
// Created by patri on 5/24/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_PARTICLESYSTEM_H
#define RHYTHMIC_PROGRAMMING_GAME_PARTICLESYSTEM_H

class ParticleAnimation;

#include <vector>
#include "ParticleAnimation.h"
#include "ParticleAnimationLink.h"
#include "ParticleProperties.h"
#include "../workspace/WorkspaceObject.h"


class ParticleSystem : public WorkspaceObject {
protected:
    std::vector<ParticleAnimationLink*> _animationLinks;

public:
    ParticleSystem();

    ParticleSystem(short x, short y, short width, short height);

    ~ParticleSystem() override;

    void Update(AudioPlayer* audioPlayer) override;

    void Initialize() override;

    void Clear() override;

    void SetAlign(float x, float y);

    void SetPosition(short x, short y);

    void Play(ParticleAnimation* animation, unsigned long start);
};


#endif //RHYTHMIC_PROGRAMMING_GAME_PARTICLESYSTEM_H
