//
// Created by patri on 5/25/2018.
//

#include "ParticleTemplate.h"

ParticleTemplate::ParticleTemplate(unsigned int start, unsigned int duration, Texture* texture,
                                   const ParticleProperties& startProperties,
                                   const ParticleProperties& endProperties,
                                   float horizontalAlign, float verticalAlign) :
        _start(start),
        _duration(duration),
        _texture(texture),
        _startProperties(startProperties),
        _endProperties(endProperties),
        _horizontalAlign(horizontalAlign),
        _verticalAlign(verticalAlign) {}

unsigned int ParticleTemplate::GetStart() {
    return _start;
}

unsigned int ParticleTemplate::GetDuration() {
    return _duration;
}

Texture* ParticleTemplate::GetTexture() {
    return _texture;
}

ParticleProperties ParticleTemplate::GetStartProperties() {
    return _startProperties;
}

ParticleProperties ParticleTemplate::GetEndProperties() {
    return _endProperties;
}

float ParticleTemplate::GetHorizontalAlign() {
    return _horizontalAlign;
}

float ParticleTemplate::GetVerticalAlign() {
    return _verticalAlign;
}

