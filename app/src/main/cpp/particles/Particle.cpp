//
// Created by pw on 29-5-2018.
//

#include "Particle.h"

Particle::Particle(Texture* texture, ParticleProperties startProperties,
                   ParticleProperties endProperties,
                   unsigned long start, unsigned long duration, float horizontalAlign,
                   float verticalAlign) :
        _sprite(new Sprite(texture)),
        _startProperties(startProperties),
        _endProperties(endProperties),
        _start(start),
        _duration(duration),
        _horizontalAlign(horizontalAlign),
        _verticalAlign(verticalAlign) {
    ServiceManager::GetInstance().Send(new Message{
            ADD_BACKGROUND_OBJECT2D,
            _sprite
    });
}

Particle::~Particle() {
    ServiceManager::GetInstance().Send(new Message{
            REMOVE_BACKGROUND_OBJECT2D,
            _sprite
    });

    delete _sprite;
}

void Particle::Update(unsigned long milliseconds) {
    float delta = static_cast<float>(milliseconds - _start) /
                  _duration; //Interpolation::Bounce(static_cast<float>(milliseconds - _start) / _duration);

    //Update Position, Scale and Rotation of sprite
    glm::vec3 position = _startProperties.position +
                         ((_endProperties.position - _startProperties.position) * delta);
    glm::vec3 scale =
            _startProperties.scale + ((_endProperties.scale - _startProperties.scale) * delta);
    float alpha =
            _startProperties.alpha + ((_endProperties.alpha - _startProperties.alpha) * delta);
    glm::quat rotation = _startProperties.rotation; //- _startProperties.position * delta;

    _sprite->SetPosition(
            position - glm::vec3(scale.x * _horizontalAlign, scale.y * _verticalAlign, 0));
    _sprite->SetScale(scale);

    //Only change alpha to not disturb performance colors
    _sprite->SetAlpha(alpha);
    _sprite->SetRotation(rotation);

    if (milliseconds > _start + _duration) _isDone = true;
}

bool Particle::IsDone() {
    return _isDone;
}
