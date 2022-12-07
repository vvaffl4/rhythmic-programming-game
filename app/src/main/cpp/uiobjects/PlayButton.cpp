//
// Created by michelle on 08/06/18.
//

#include "PlayButton.h"
#include "../MainGame.h"

PlayButton::PlayButton(AAssetManager* assetManager, short x, short y)
        : TexturedButton(assetManager, "button_play.png", x, y, 280, 180) {
}

PlayButton::~PlayButton() {}

void PlayButton::OnButtonDown() {
    if (!_hasLevel) return;

    std::string levelPath = "levels/";
    levelPath += _level;

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
            &levelPath
    });

    ServiceManager::GetInstance().Send(new Message{
            MessageType::START_GAME,
            NULL
    });
}

void PlayButton::OnButtonUp() {

}

void PlayButton::SetLevel(std::string level) {
    _hasLevel = true;
    _level = level;
}


void PlayButton::ClearLevel() {
    _hasLevel = false;
}
