//
// Created by pw on 14-5-2018.
//

#include "StartButton.h"

StartButton::StartButton(short x, short y) : UIButton(x, y, 490, 280) {}

void StartButton::OnButtonUp() {

}

void StartButton::OnButtonDown() {
    ServiceManager::GetInstance().Send(new Message{
            UNRENDER_ALL_STRINGS,
            NULL
    });

    ServiceManager::GetInstance().Send(new Message{
            MessageType::PLAY_AUDIO_CONFIRM,
            NULL
    });

    ServiceManager::GetInstance().Send(new Message{
            SET_UISCENE,
            new LevelSelectionScreen(0, 0)
    });
}
