//
// Created by Maarten on 29-5-2018.
//

#include "BeatExplosion.h"

BeatExplosion::BeatExplosion(bool lane, float tapAudioPosition) {
    _lane = lane;
    _tapAudioPosition = tapAudioPosition;
    _width = 100;
    _height = 100;
    _sprite = new Sprite(ResourceManager::GetInstance().GetTexture("workspace_beat_explosion"));

    if (_lane) { // Right Lane
        _sprite->SetPosition(glm::vec3((Properties.WIDTH * 0.82f) - (_width / 2),
                                       (Properties.HEIGHT * 0.8f) - (_height / 2), 0));
    } else { // Left Lane
        _sprite->SetPosition(glm::vec3((Properties.WIDTH * 0.18f) - (_width / 2),
                                       (Properties.HEIGHT * 0.8f) - (_height / 2), 0));
    }
    _sprite->SetScale(_width, _height, 1);
}

BeatExplosion::~BeatExplosion() {
    delete _sprite;
}

void BeatExplosion::Update(AudioPlayer* audioPlayer) {
    float delta = audioPlayer->GetPosition() - _tapAudioPosition;

    if (delta == 0.0f) return;

    float scale = (1 + (delta / 380) * 3.0f);
    if (_lane) { // Right Lane
        _sprite->SetPosition(glm::vec3((Properties.WIDTH * 0.82f) - (_width * scale / 2),
                                       (Properties.HEIGHT * 0.8f) - (_height * scale / 2), 0));
    } else { // Left Lane
        _sprite->SetPosition(glm::vec3((Properties.WIDTH * 0.18f) - (_width * scale / 2),
                                       (Properties.HEIGHT * 0.8f) - (_height * scale / 2), 0));
    }
    _sprite->SetScale(scale * _width, scale * _height, 1);

    if (scale >= 3.0f) {
        ServiceManager::GetInstance().Send(
                new Message{MessageType::REMOVE_BACKGROUND_OBJECT2D, _sprite});
        _toBeDeleted = true;
    }
}

void BeatExplosion::Initialize() {
    ServiceManager::GetInstance().Send(new Message{
            ADD_BACKGROUND_OBJECT2D,
            _sprite
    });
}

void BeatExplosion::Clear() {
    if (_sprite != nullptr) {
        ServiceManager::GetInstance().Send(
                new Message{MessageType::REMOVE_BACKGROUND_OBJECT2D, _sprite});
    }
}
