//
// Created by michelle on 13/06/18.
//

#include "LevelSelectionButton.h"
#include "../screens/LevelSelectionScreen.h"

LevelSelectionButton::LevelSelectionButton(AAssetManager* assetManager, short x, short y)
        : TexturedButton(assetManager, "result_screen_back_to_main.png", x, y, 280, 180) {


}

void LevelSelectionButton::OnButtonUp() {

}

void LevelSelectionButton::OnButtonDown() {
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
