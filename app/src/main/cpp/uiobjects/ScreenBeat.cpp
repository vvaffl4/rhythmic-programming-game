//
// Created by patri on 4/26/2018.
//

#include "ScreenBeat.h"

ScreenBeat::ScreenBeat(Beat beat, LaneSide laneSide, short targetX, short targetY, BeatType type) :
        UIObject(targetX, targetY - Properties.HEIGHT, static_cast<short>(167),
                 static_cast<short>(167)),
        _beat(beat),
        _laneSide(laneSide),
        _targetX(targetX),
        _targetY(targetY),
        _beatType(type) {}

void ScreenBeat::ProcessInput(Input* input) {
    /*
     * Needed for input loop
     */
}

void ScreenBeat::SetTexture(Texture* texture) {
    _sprite->SetTexture(texture);
}

void ScreenBeat::Update(float audioPosition) {

    float delta = audioPosition - _beat.position;

    if (delta == 0.0f) return;

    short distance = static_cast<short>((delta / 1000) * Properties.HEIGHT);
    SetY(_targetY + distance);
}

float ScreenBeat::GetBeatPosition() {
    return _beat.position;
}

LaneSide ScreenBeat::GetLaneSide() {
    return _laneSide;
}

float ScreenBeat::GetBeatDuration() {
    return _beat.duration;
}

BeatType ScreenBeat::GetBeatType() {
    return _beatType;
}

void ScreenBeat::SetBeatPressed(bool pressed) {
    _isPressed = pressed;
}

bool ScreenBeat::GetBeatPressed() {
    return _isPressed;
}

void ScreenBeat::_initializeBeat() {
    GetSprite()->SetZIndex(1);
    SetAlign(ScreenBeat::CENTER, ScreenBeat::CENTER);
}


