//
// Created by patri on 5/24/2018.
//

#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() :
        WorkspaceObject() {}

ParticleSystem::ParticleSystem(short x, short y, short width, short height) :
        WorkspaceObject(x, y, width, height) {}

ParticleSystem::~ParticleSystem() {
    for (auto animationIt = _animationLinks.begin();
         animationIt != _animationLinks.end(); ++animationIt) {
        for (auto particleIt = (*animationIt)->animationParticles.begin();
             particleIt != (*animationIt)->animationParticles.end(); ++particleIt) {
            delete *particleIt;
        }
        (*animationIt)->animationParticles.clear();

        delete *animationIt;
    }
    _animationLinks.clear();
}

void ParticleSystem::Update(AudioPlayer* audioPlayer) {

    unsigned long position = audioPlayer->GetPosition();

    std::vector<ParticleAnimationLink*> rubbish;

    //Update AnimationLinks
    for (auto animationLinkIt = _animationLinks.begin();
         animationLinkIt != _animationLinks.end(); ++animationLinkIt) {

        (*animationLinkIt)->particleAnimation->Update(*animationLinkIt,
                                                      position);//&((*animationLinkIt)->_animationParticles), (*animationLinkIt)->_particleIndex, (*animationLinkIt)->start, position);

        if ((*animationLinkIt)->isDone) {
            rubbish.push_back((*animationLinkIt));
        }
    }

    for (int i = 0, il = static_cast<int>(rubbish.size()); i < il; ++i) {
        _animationLinks.erase(
                std::remove(_animationLinks.begin(), _animationLinks.end(), rubbish[i]),
                _animationLinks.end());
        delete rubbish[i];
    }
}

void ParticleSystem::Initialize() {}

void ParticleSystem::Clear() {
    for (auto animationIt = _animationLinks.begin();
         animationIt != _animationLinks.end(); ++animationIt) {
        for (auto particleIt = (*animationIt)->animationParticles.begin();
             particleIt != (*animationIt)->animationParticles.end(); ++particleIt) {
            delete *particleIt;
        }
        (*animationIt)->animationParticles.clear();

        delete *animationIt;
    }
    _animationLinks.clear();
}

void ParticleSystem::Play(ParticleAnimation* animation, unsigned long start) {
    _animationLinks.push_back(new ParticleAnimationLink{
            animation,
            std::vector<Particle*>(),
            ParticleProperties{},
            0,
            start,
            false,
            false
    });
}

void ParticleSystem::SetAlign(float x, float y) {
    WorkspaceObject::SetAlign(x, y);
}

void ParticleSystem::SetPosition(short x, short y) {
    WorkspaceObject::SetPosition(x, y);
}