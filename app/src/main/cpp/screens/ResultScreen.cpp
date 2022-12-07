//
// Created by Anne on 16-5-2018.
//

#include "ResultScreen.h"

ResultScreen::ResultScreen(short x, short y, LevelScore* levelScore) :
        UIScene(x, y, static_cast<short>(Properties.WIDTH), static_cast<short>(Properties.HEIGHT)),
        _levelScore(levelScore) {}

void ResultScreen::Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) {

    ResourceManager& resourceManager = ResourceManager::GetInstance();
    _initializeResources(assetManager, resourceManager);

    ReplayButton* replayButton = new ReplayButton(840, 620);
    replayButton->SetLevel(_levelScore->level);
    replayButton->SetAlign(UIObject::CENTER, UIObject::CENTER);
    replayButton->GetSprite()->SetTexture(resourceManager.GetTexture("result_screen_retry"));

    MainMenuButton* mainMenuButton = new MainMenuButton(440, 620);
    mainMenuButton->SetAlign(UIObject::CENTER, UIObject::CENTER);
    mainMenuButton->GetSprite()->SetTexture(
            resourceManager.GetTexture("result_screen_back_to_main"));

    _objects.push_back(replayButton);
    _objects.push_back(mainMenuButton);

    glm::vec3 color = glm::vec3(1.0f);
    ServiceManager::GetInstance().Send(new Message{
            SET_SCENE_COLOR,
            &color
    });

    for (auto objectIt = _objects.begin(); objectIt != _objects.end(); ++objectIt) {
        ServiceManager::GetInstance().Send(new Message{
                ADD_OBJECT2D,
                (*objectIt)->GetSprite()
        });
    }

    _sendScoreMessage();
    _sendHitScoreMessage();
    _sendComboScoreMessage();
    _sendAccuracyScoreMessage();
    _sendHighscoreScoreMessage();
}

void ResultScreen::_sendScoreMessage() {
    std::string score = "";
    if (_levelScore->placement != 0) {
        score = std::to_string(_levelScore->placement) + "&:&" +
                std::to_string(_levelScore->score);
    } else {
        score = std::to_string(_levelScore->score);
    }

    StringRenderData srdScore{"score", "white-font.ini",
                              score.c_str(),
                              0.5f, 640, 60, StringAlignment::ALIGN_CENTER, 0.0f};
    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            &srdScore
    });
}

void ResultScreen::_sendHitScoreMessage() {
    int i = 0;

    for (auto amountIt = _levelScore->amounts.begin();
         amountIt != _levelScore->amounts.end(); ++amountIt) {

        std::string hitScore = std::to_string((*amountIt).second);
        std::string hit = "";

        std::string hitKey = "hitType";
        std::string resultKey = "resultScore";

        switch ((*amountIt).first) {
            case 0: {
                hit = "PERFECT";
            }
                break;
            case 1: {
                hit = "GREAT";
            }
                break;
            case 2: {
                hit = "GOOD";
            }
                break;
            case 3: {
                hit = "BAD";
            }
                break;
            case 4: {
                hit = "MISSED";
            }
                break;
        }

        ServiceManager::GetInstance().Send(new Message{
                MessageType::RENDER_STRING,
                new StringRenderData{(new std::string(hitKey + std::to_string(i)))->c_str(),
                                     "abc-font.ini",
                                     (hit + ":").c_str(),
                                     0.25f, 430, 250 + i * 55, StringAlignment::ALIGN_RIGHT, 0.0f}
        });

        ServiceManager::GetInstance().Send(new Message{
                MessageType::RENDER_STRING,
                new StringRenderData{(new std::string(resultKey + std::to_string(i)))->c_str(),
                                     "white-font.ini",
                                     (hitScore + "X").c_str(),
                                     0.25f, 470, 250 + i * 55, StringAlignment::ALIGN_LEFT, 0.0f}
        });

        i++;
    }
}


void ResultScreen::_sendComboScoreMessage() {

    std::string highestCombo = std::to_string(_levelScore->highestCombo);
    std::string highestLabel = "Max&&Combo";

    std::string highestLabelKey = "highestLabelKey";
    std::string highestComboKey = "highestComboKey";


    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            new StringRenderData{(new std::string(highestLabelKey))->c_str(), "abc-font.ini",
                                 (highestLabel + ":").c_str(),
                                 0.25f, 940, 250, StringAlignment::ALIGN_RIGHT, 0.0f}
    });


    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            new StringRenderData{(new std::string(highestComboKey))->c_str(), "white-font.ini",
                                 (highestCombo + "X").c_str(),
                                 0.25f, 980, 250, StringAlignment::ALIGN_LEFT, 0.0f}
    });
}

void ResultScreen::_sendAccuracyScoreMessage() {

    std::string accuracy = std::to_string(floor((_levelScore->accuracy * 100) + .5) / 100);
    std::string roundAccuracy = accuracy.substr(0, 5);
    std::string accuracyLabel = "Accuracy";

    std::string accuracyLabelKey = "accuracyLabelKey";
    std::string accuracyKey = "accuracyKey";


    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            new StringRenderData{(new std::string(accuracyLabelKey))->c_str(), "abc-font.ini",
                                 (accuracyLabel + ":").c_str(),
                                 0.25f, 940, 305, StringAlignment::ALIGN_RIGHT, 0.0f}
    });


    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            new StringRenderData{(new std::string(accuracyKey))->c_str(), "white-font.ini",
                                 (roundAccuracy + "%").c_str(),
                                 0.25f, 980, 305, StringAlignment::ALIGN_LEFT, 0.0f}
    });
}

void ResultScreen::Release() {

    for (auto objectIt = _objects.begin(); objectIt != _objects.end(); ++objectIt) {
        ServiceManager::GetInstance().Send(new Message{
                REMOVE_OBJECT2D,
                (*objectIt)->GetSprite()
        });
    }

    ServiceManager::GetInstance().Send(new Message{
            UNRENDER_ALL_STRINGS,
            nullptr
    });

    ResourceManager::GetInstance().ReleaseResources();
}

void ResultScreen::_sendHighscoreScoreMessage() {

    std::string highscoreLabel = "BEST:";

    StringRenderData srdHighscoreLabel{"highscoreLabel", "abc-font.ini",
                                       (highscoreLabel).c_str(),
                                       0.275f, 610, 150, StringAlignment::ALIGN_RIGHT, 0.0f};
    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            &srdHighscoreLabel
    });

    StringRenderData srdHighscore{"highscore", "white-font.ini",
                                  std::to_string(_levelScore->highscore).c_str(),
                                  0.275f, 640, 150, StringAlignment::ALIGN_LEFT, 0.0f};
    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            &srdHighscore
    });
}

void
ResultScreen::_initializeResources(AAssetManager* assetManager, ResourceManager& resourceManager) {
    /*
     * Set resources that are being used
     */
    resourceManager.SetResource("main_menu_background",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "main_menu_background.png"));
    resourceManager.SetResource("result_screen_retry",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "result_screen_retry.png"));
    resourceManager.SetResource("result_screen_back_to_main",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "result_screen_back_to_main.png"));
}
