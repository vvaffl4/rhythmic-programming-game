//
// Created by patri on 6/6/2018.
//

#include "TitleScreen.h"
#include "LevelSelectionScreen.h"

TitleScreen::TitleScreen(short x, short y) :
        UIScene(x, y, static_cast<short>(Properties.WIDTH),
                static_cast<short>(Properties.HEIGHT)) {}

void TitleScreen::Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) {

    ResourceManager& resourceManager = ResourceManager::GetInstance();
    _initializeResources(assetManager, resourceManager);

    UIImage* titleScreenBackground = new UIImage(0, 0, static_cast<short>(Properties.WIDTH),
                                                 static_cast<short>(Properties.HEIGHT));
    titleScreenBackground->GetSprite()->SetTexture(
            resourceManager.GetTexture("title_screen_background"));

    UIImage* titleScreenOverlay = new UIImage(0, 0, static_cast<short>(Properties.WIDTH),
                                              static_cast<short>(Properties.HEIGHT));
    titleScreenOverlay->GetSprite()->SetTexture(resourceManager.GetTexture("title_screen_overlay"));

    UIImage* titleScreenLogo = new UIImage(0, 0, static_cast<short>(Properties.WIDTH),
                                           static_cast<short>(Properties.HEIGHT));
    titleScreenLogo->GetSprite()->SetTexture(resourceManager.GetTexture("title_screen_logo"));

    UIImage* titleScreenTap = new UIImage(640, 600,
                                          static_cast<short>(Properties.WIDTH * 0.1171875f),
                                          static_cast<short>(Properties.HEIGHT * 0.111f));
    titleScreenTap->SetAlign(UIObject::CENTER, UIObject::CENTER);
    titleScreenTap->GetSprite()->SetTexture(resourceManager.GetTexture("title_screen_tap"));

    _objects.push_back(titleScreenBackground);
    _objects.push_back(titleScreenOverlay);
    _objects.push_back(titleScreenLogo);
    _objects.push_back(titleScreenTap);

    for (auto objectIt = _objects.begin(); objectIt != _objects.end(); ++objectIt) {

        ServiceManager::GetInstance().Send(new Message{
                ADD_OBJECT2D,
                (*objectIt)->GetSprite()
        });
    }

    ServiceManager::GetInstance().Send(new Message{
            MessageType::PLAY_AUDIO_MAIN_MENU_MUSIC, NULL
    });
}

void TitleScreen::Release() {

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

void TitleScreen::ProcessInput(Input* input) {

    if (input->type == InputType::UP) {
        ServiceManager::GetInstance().Send(new Message{
                SET_UISCENE,
                new LevelSelectionScreen(0, 0)
        });

        ServiceManager::GetInstance().Send(new Message{
                SWITCH_SCREEN,
                NULL
        });
    }
}

void
TitleScreen::_initializeResources(AAssetManager* assetManager, ResourceManager& resourceManager) {
    /*
     * Set resources that are being used
     */
    resourceManager.SetResource("title_screen_overlay",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "title_screen_overlay.png"));
    resourceManager.SetResource("title_screen_logo",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "title_screen_logo.png"));
    resourceManager.SetResource("title_screen_tap",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "title_screen_tap_to_start.png"));
    resourceManager.SetResource("title_screen_background",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "title_screen_background.png"));
}
