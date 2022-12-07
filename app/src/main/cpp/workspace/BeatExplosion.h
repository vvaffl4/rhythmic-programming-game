//
// Created by Maarten on 29-5-2018.
//

#ifndef RHYTHMICPROGRAMMINGBB_BEATEXPLOSION_H
#define RHYTHMICPROGRAMMINGBB_BEATEXPLOSION_H

#include "../sprite/Sprite.h"
#include "WorkspaceObject.h"
#include "../properties.h"
#include "../services/ServiceManager.h"
#include "../ResourceManager.h"

class BeatExplosion : public WorkspaceObject {
protected:
    bool _lane;
    float _tapAudioPosition;
    int _width;
    int _height;
    Sprite* _sprite = nullptr;

public:
    BeatExplosion(bool lane, float tapAudioPosition);

    ~BeatExplosion();

    void Update(AudioPlayer* audioPlayer) override;

    void Initialize() override;

    void Clear() override;
};


#endif //RHYTHMICPROGRAMMINGBB_BEATEXPLOSION_H
