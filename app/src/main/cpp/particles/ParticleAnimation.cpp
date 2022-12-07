//
// Created by patri on 5/25/2018.
//

#include "ParticleAnimation.h"

ParticleAnimation::ParticleAnimation() {}

ParticleAnimation::~ParticleAnimation() {
    for (auto it = _particleTemplates.begin(); it != _particleTemplates.end(); ++it) {
        delete *it;
    }
    _particleTemplates.clear();
}

void ParticleAnimation::QueueParticle(ParticleTemplate* particle) {
    _particleTemplates.push_back(particle);
}

void ParticleAnimation::Update(ParticleAnimationLink* particleAnimationLink,
                               unsigned long milliSeconds) {

    // Check if particles need to be added
    _addProximityParticle(particleAnimationLink,
                          milliSeconds);//particles, index, start, milliSeconds);

    // Update existing particles
    _updateProximityParticles(particleAnimationLink,
                              milliSeconds);//particles, index, milliSeconds);

    // CHeck if particles need to be deleted
    _removeProximityParticles(particleAnimationLink,
                              milliSeconds);//particles, index, milliSeconds);
}

void ParticleAnimation::_addProximityParticle(ParticleAnimationLink* particleAnimationLink,
                                              unsigned long milliSeconds) {//std::vector<Particle*>* particles, unsigned int& index, unsigned long start, unsigned long milliSeconds) {

    //Get Current values from ParticleAnimationLink
    unsigned int index = particleAnimationLink->particleIndex;
    const unsigned long start = particleAnimationLink->start;
    const bool custom = particleAnimationLink->isCustom;

    //Loop through particles that are not spawned yet
    while (index < _particleTemplates.size()) {

        //If milliseconds is past start time
        if (start + _particleTemplates[index]->GetStart() < milliSeconds) {

            ParticleProperties startProperties = _particleTemplates[index]->GetStartProperties();

            if (custom)
                startProperties = particleAnimationLink->customParticleProperties;

            //Create and add Particle to the ParticleAnimationLink
            particleAnimationLink->animationParticles.push_back(
                    new Particle(_particleTemplates[index]->GetTexture(),
                                 startProperties,
                                 _particleTemplates[index]->GetEndProperties(),
                                 _particleTemplates[index]->GetStart() + start,
                                 _particleTemplates[index]->GetDuration(),
                                 _particleTemplates[index]->GetHorizontalAlign(),
                                 _particleTemplates[index]->GetVerticalAlign()));
        } else {
            break;
        }

        //Up the index to the next particle that hasn't spawned yet
        ++index;
    }

    //Set the particleIndex to the current index that hasn't been spawned
    particleAnimationLink->particleIndex = index;
}

void ParticleAnimation::_updateProximityParticles(ParticleAnimationLink* particleAnimationLink,
                                                  unsigned long milliSeconds) {

    //Update all particles in the particleAnimation Link
    for (auto particleIt = particleAnimationLink->animationParticles.begin();
         particleIt != particleAnimationLink->animationParticles.end(); ++particleIt) {
        (*particleIt)->Update(milliSeconds);
    }
}

void ParticleAnimation::_removeProximityParticles(ParticleAnimationLink* particleAnimationLink,
                                                  unsigned long milliSeconds) {

    std::vector<Particle*> rubbish;

    //Loop through all particles that are being shown
    for (int i = 0, il = static_cast<int>(particleAnimationLink->animationParticles.size());
         i < il; ++i) {

        //Check if current particle is done
        if (particleAnimationLink->animationParticles[i]->IsDone()) {

            //Remove particle from particle vector of ParticleAnimationLInk
            rubbish.push_back(particleAnimationLink->animationParticles[i]);
        }
    }

    for (int i = 0, il = static_cast<int>(rubbish.size()); i < il; ++i) {
        particleAnimationLink->animationParticles.erase(
                std::remove(particleAnimationLink->animationParticles.begin(),
                            particleAnimationLink->animationParticles.end(),
                            rubbish[i]),
                particleAnimationLink->animationParticles.end());
        delete rubbish[i];
    }

    if (particleAnimationLink->particleIndex >= _particleTemplates.size() &&
        particleAnimationLink->animationParticles.empty()) {
        particleAnimationLink->isDone = true;
    }
}
