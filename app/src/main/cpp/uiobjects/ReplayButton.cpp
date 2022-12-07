//
// Created by jaron on 24-5-2018.
//

#include "ReplayButton.h"

ReplayButton::ReplayButton(short x, short y) :
        UIButton(x, y, 350, 200) {}

void ReplayButton::OnButtonUp() {

}

void ReplayButton::OnButtonDown() {
    if (!_hasLevel) return;

    ServiceManager::GetInstance().Send(new Message{
            UNRENDER_ALL_STRINGS,
            NULL
    });

    ServiceManager::GetInstance().Send(new Message{
            SET_UISCENE,
            new MainGame(0, 0)
    });

    ServiceManager::GetInstance().Send(new Message{
            MessageType::LOAD_GAME,
            &_level
    });

    ServiceManager::GetInstance().Send(new Message{
            MessageType::START_GAME,
            NULL
    });

    ServiceManager::GetInstance().Send(new Message{
            MessageType::PLAY_AUDIO_CONFIRM,
            NULL
    });
}

void ReplayButton::SetLevel(std::string level) {
    _hasLevel = true;
    _level = level;
}