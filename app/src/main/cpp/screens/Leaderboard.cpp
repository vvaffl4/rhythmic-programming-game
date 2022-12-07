//
// Created by jaron on 5-6-2018.
//

#include "Leaderboard.h"

Leaderboard::Leaderboard(int x, int y, std::string levelName) :
        UIScene(x, y, static_cast<short>(Properties.WIDTH),
                static_cast<short>(Properties.HEIGHT)) {

    _levelName = levelName;
}

void Leaderboard::Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) {


    ResourceManager& resourceManager = ResourceManager::GetInstance();
    _initializeResources(assetManager, resourceManager);

    _levelSelectionButton = new LevelSelectionButton(assetManager, 800, 600);
    _levelSelectionButton->CenterHorizontally();
    _levelSelectionButton->SetYFromBottom(10);
    _objects.push_back(_levelSelectionButton);

    for (auto objectIt = _objects.begin(); objectIt != _objects.end(); ++objectIt) {
        ServiceManager::GetInstance().Send(new Message{
                ADD_OBJECT2D,
                (*objectIt)->GetSprite()
        });
    }

    _sendLeaderboardMessage(nativeActivity);
}

void Leaderboard::_sendLeaderboardMessage(ANativeActivity* nativeActivity) {
    LevelHighscore lh = HighscoreFactory::GetInstance().Load(nativeActivity, _levelName);
    int incrementY = 0;
    int X_offside = 0;

    for (int i = 0; i < sizeof(lh.scores) / sizeof(lh.scores[0]); i++) {
        std::string highScore = std::to_string(lh.scores[i]);
        std::string placement = std::to_string(i + 1);

        std::string placementKey = "placement";
        std::string highScoreKey = "highScore";

        /* Sends a message to show the placement number on the screen
         */
        ServiceManager::GetInstance().Send(new Message{
                MessageType::RENDER_STRING,
                new StringRenderData{(new std::string(placementKey + std::to_string(i)))->c_str(),
                                     "white-font.ini",
                                     (placement + ":").c_str(),
                                     0.45f, 140 + X_offside, 50 + incrementY * 90,
                                     StringAlignment::ALIGN_RIGHT, 0.0f}
        });

        /* Sends a message to show the text score for a specific placement number on the screen
         */
        ServiceManager::GetInstance().Send(new Message{
                MessageType::RENDER_STRING,
                new StringRenderData{(new std::string(highScoreKey + std::to_string(i)))->c_str(),
                                     "white-font.ini",
                                     (highScore).c_str(),
                                     0.45f, 190 + X_offside, 50 + incrementY * 90,
                                     StringAlignment::ALIGN_LEFT, 0.0f}
        });

        incrementY++;

        if (incrementY > 4) {
            incrementY = 0;
            X_offside = 610;
        }
    }
}

void Leaderboard::Release() {
    if (_levelSelectionButton != nullptr) {
//        delete _levelSelectionButton;
        _levelSelectionButton = nullptr;
    }

    ServiceManager::GetInstance().Send(new Message{
            REMOVE_OBJECT2D,
            _sprite
    });

    for (auto objectIt = _objects.begin(); objectIt != _objects.end(); ++objectIt) {
        ServiceManager::GetInstance().Send(new Message{
                REMOVE_OBJECT2D,
                (*objectIt)->GetSprite()
        });
    }

    ResourceManager::GetInstance().ReleaseResources();
}

void
Leaderboard::_initializeResources(AAssetManager* assetManager, ResourceManager& resourceManager) {
    /*
     * Set resources that are being used
     */
    resourceManager.SetResource("main_menu_background",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "main_menu_background.png"));
    resourceManager.SetResource("result_screen_back_to_main",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "result_screen_back_to_main.png"));
}
