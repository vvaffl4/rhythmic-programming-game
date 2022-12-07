//
// Created by Anne on 25-5-2018.
//

#include "TapBeat.h"

TapBeat::TapBeat(Beat beat, LaneSide laneSide, short targetX, short targetY) :
        ScreenBeat(beat, laneSide, targetX, targetY, BeatType::TAPBEAT) {
    _initializeBeat();
}

float TapBeat::GetBeatEnd() {
    return _beat.position;
}

void TapBeat::_initializeBeat() {
    ResourceManager& resourceManager = ResourceManager::GetInstance();

    _sprite = new Sprite(resourceManager.GetTexture("tap_beat"));
    _sprite->SetScale(glm::vec3(_width, _height, 1));
    _sprite->SetZIndex(1);

    SetAlign(UIObject::CENTER, UIObject::CENTER);

    ServiceManager::GetInstance().Send(new Message{
            MessageType::ADD_OBJECT2D,
            _sprite
    });
}

void TapBeat::Update(float audioPosition) {
    float delta = audioPosition - _beat.position;

    if (delta == 0.0f) return;

    short distance = static_cast<short>((delta / 1000) * Properties.HEIGHT);
    _y = _targetY + distance;

    if (_sprite != nullptr) {
        _sprite->SetPosition(glm::vec3(
                _x - (_width * _horizontalAlign),
                _y - (_height * _verticalAlign),
                0));
    }
}

void TapBeat::ClearBeat() {
    ServiceManager::GetInstance().Send(new Message{
            MessageType::REMOVE_OBJECT2D,
            _sprite
    });
}
