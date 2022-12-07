//
// Created by pw on 22-4-2018.
//

#include "BeatHitDetectionButton.h"

BeatHitDetectionButton::BeatHitDetectionButton(LaneSide side) :
        UIButton(0, 0, static_cast<short>(250), static_cast<short>(250)),
        _side(side) {

    _upTexture = ResourceManager::GetInstance().GetTexture("main_game_touch_area_up");
    _downTexture = ResourceManager::GetInstance().GetTexture("main_game_touch_area_down");
    _sprite->SetTexture(_upTexture);
}

void BeatHitDetectionButton::OnButtonUp() {
    _sprite->SetTexture(_upTexture);
    ServiceManager::GetInstance().Send(new Message{
            MessageType::ON_BUTTON_RELEASE,
            &_side
    });
}

void BeatHitDetectionButton::OnButtonDown() {
    _sprite->SetTexture(_downTexture);
    ServiceManager::GetInstance().Send(new Message{
            MessageType::ON_BUTTON_PRESS,
            &_side
    });
}

void BeatHitDetectionButton::SetUpTexture(Texture* texture) {
    _upTexture = texture;
    _sprite->SetTexture(_upTexture);
}

void BeatHitDetectionButton::SetDownTexture(Texture* texture) {
    _downTexture = texture;
}
