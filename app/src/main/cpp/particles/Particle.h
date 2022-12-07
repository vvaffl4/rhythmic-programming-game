//
// Created by pw on 29-5-2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_PARTICLE_H
#define RHYTHMIC_PROGRAMMING_GAME_PARTICLE_H

#include "ParticleTemplate.h"
#include "../render/Texture.h"
#include "../sprite/Sprite.h"
#include "../services/ServiceManager.h"

class Particle {
private:
    Sprite* _sprite = nullptr;
    unsigned long _start;
    unsigned long _duration;
    float _horizontalAlign;
    float _verticalAlign;
    ParticleProperties _startProperties;
    ParticleProperties _endProperties;
    bool _isDone = false;

public:
    Particle(Texture* texture, ParticleProperties startProperties, ParticleProperties endProperties,
             unsigned long start, unsigned long duration, float horizontalAlign,
             float verticalAlign);

    ~Particle();

    void Update(unsigned long milliseconds);

    bool IsDone();
};


#endif //RHYTHMIC_PROGRAMMING_GAME_PARTICLE_H
