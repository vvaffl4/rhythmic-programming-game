//
// Created by Anne on 16-5-2018.
//

#include "MainMenuButton.h"
#include "../screens/LevelSelectionScreen.h"

MainMenuButton::MainMenuButton(short x, short y) :
        UIButton(x, y, 350, 200) {}

void MainMenuButton::OnButtonUp() {

}

void MainMenuButton::OnButtonDown() {
    ServiceManager::GetInstance().Send(new Message{
            UNRENDER_ALL_STRINGS,
            NULL
    });
    ServiceManager::GetInstance().Send(new Message{
            SET_UISCENE,
            new LevelSelectionScreen(0, 0)
    });

    ServiceManager::GetInstance().Send(new Message{
            PLAY_AUDIO_CANCEL,
            NULL
    });
}
