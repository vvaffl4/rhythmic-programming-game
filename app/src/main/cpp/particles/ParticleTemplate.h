//
// Created by patri on 5/25/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_PARTICLE_TEMPLATE_H
#define RHYTHMIC_PROGRAMMING_GAME_PARTICLE_TEMPLATE_H

#include "../render/Texture.h"
#include "ParticleProperties.h"

class ParticleTemplate {
private:

    unsigned int _start;
    unsigned int _duration;
    Texture* _texture = nullptr;
    ParticleProperties _startProperties;
    ParticleProperties _endProperties;
    float _horizontalAlign;
    float _verticalAlign;

public:
    ParticleTemplate(unsigned int start, unsigned int duration, Texture* texture,
                     const ParticleProperties& startProperties,
                     const ParticleProperties& endProperties,
                     float horizontalAlign, float verticalAlign);

    unsigned int GetStart();

    unsigned int GetDuration();

    Texture* GetTexture();

    ParticleProperties GetStartProperties();

    ParticleProperties GetEndProperties();

    float GetVerticalAlign();

    float GetHorizontalAlign();
};


#endif //RHYTHMIC_PROGRAMMING_GAME_PARTICLE_H
