//
// Created by pw on 15-5-2018.
//

#include "MainGame.h"

MainGame::MainGame(short x, short y) :
        UIScene(x, y, static_cast<short>(Properties.WIDTH),
                static_cast<short>(Properties.HEIGHT)) {}

void MainGame::Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) {
    ResourceManager& resourceManager = ResourceManager::GetInstance();
    _initializeResources(assetManager, resourceManager);

    BeatHitDetectionButton* beatHitDetectionButtonLeft = new BeatHitDetectionButton(LaneSide::LEFT);
    beatHitDetectionButtonLeft->SetPosition(static_cast<short>(Properties.WIDTH * 0.18f),
                                            static_cast<short>(Properties.HEIGHT * 0.8f));
    beatHitDetectionButtonLeft->SetAlign(UIObject::CENTER, UIObject::CENTER);

    BeatHitDetectionButton* beatHitDetectionButtonRight = new BeatHitDetectionButton(
            LaneSide::RIGHT);
    beatHitDetectionButtonRight->SetPosition(static_cast<short>(Properties.WIDTH * 0.82f),
                                             static_cast<short>(Properties.HEIGHT * 0.8f));
    beatHitDetectionButtonRight->SetAlign(UIObject::CENTER, UIObject::CENTER);

    /*
     * Create Lanes
     */
    BeatLane* testLaneLeft = new BeatLane();
    testLaneLeft->SetPosition(static_cast<short>(Properties.WIDTH * 0.18f),
                              static_cast<short>(Properties.HEIGHT * 0.41f));
    testLaneLeft->SetAlign(UIObject::CENTER, UIObject::CENTER);

    BeatLane* testLaneRight = new BeatLane();
    testLaneRight->SetPosition(static_cast<short>(Properties.WIDTH * 0.82f),
                               static_cast<short>(Properties.HEIGHT * 0.41f));
    testLaneRight->SetAlign(UIObject::CENTER, UIObject::CENTER);

    _objects.push_back(beatHitDetectionButtonLeft);
    _objects.push_back(beatHitDetectionButtonRight);
    _objects.push_back(testLaneLeft);
    _objects.push_back(testLaneRight);

    /*
     * Create UI Service and add UI
     */
    for (auto objectIt = _objects.begin(); objectIt != _objects.end(); ++objectIt) {
        ServiceManager::GetInstance().Send(new Message{
                ADD_OBJECT2D,
                (*objectIt)->GetSprite()
        });
    }

    /*
     * Add particle animations to resourceManager for explosions in middle of screen
     */
    ParticleAnimation* particleAnimation = new ParticleAnimation();
    particleAnimation->QueueParticle(new ParticleTemplate(
            0,
            900,
            resourceManager.GetTexture("workspace_beat_explosion"),
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(200.0f, 200.0f, 1.0f),
                    glm::quat(),
                    1.0f
            },
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(1700.0f, 1700.0f, 1.0f),
                    glm::quat(),
                    0.0f
            },
            0.5f,
            0.5f
    ));
    particleAnimation->QueueParticle(new ParticleTemplate(
            100,
            900,
            resourceManager.GetTexture("workspace_beat_explosion"),
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(200.0f, 200.0f, 1.0f),
                    glm::quat(),
                    1.0f
            },
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(1700.0f, 1700.0f, 1.0f),
                    glm::quat(),
                    0.0f
            },
            0.5f,
            0.5f
    ));

    ParticleAnimation* beatAnimation = new ParticleAnimation();
    beatAnimation->QueueParticle(new ParticleTemplate(
            0,
            700,
            resourceManager.GetTexture("workspace_explosion"),
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(50.0f, 50.0f, 1.0f),
                    glm::quat(),
                    1.0f
            },
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(1000.0f, 1000.0f, 1.0f),
                    glm::quat(),
                    0.0f
            },
            0.5f,
            0.5f
    ));

    ParticleAnimation* sparkAnimationVersion1 = new ParticleAnimation();
    sparkAnimationVersion1->QueueParticle(new ParticleTemplate(
            0,
            700,
            resourceManager.GetTexture("workspace_spark_explosion_version_1"),
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(50.0f, 50.0f, 1.0f),
                    glm::quat(),
                    1.0f
            },
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(4000.0f, 4000.0f, 1.0f),
                    glm::quat(),
                    0.0f
            },
            0.5f,
            0.5f
    ));

    ParticleAnimation* sparkAnimationVersion2 = new ParticleAnimation();
    sparkAnimationVersion2->QueueParticle(new ParticleTemplate(
            0,
            700,
            resourceManager.GetTexture("workspace_spark_explosion_version_2"),
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(50.0f, 50.0f, 1.0f),
                    glm::quat(),
                    1.0f
            },
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(4000.0f, 4000.0f, 1.0f),
                    glm::quat(),
                    1.0f
            },
            0.5f,
            0.5f
    ));

    ParticleAnimation* sparkAnimationVersion3 = new ParticleAnimation();
    sparkAnimationVersion3->QueueParticle(new ParticleTemplate(
            0,
            700,
            resourceManager.GetTexture("workspace_spark_explosion_version_3"),
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(50.0f, 50.0f, 1.0f),
                    glm::quat(),
                    1.0f
            },
            ParticleProperties{
                    glm::vec3(640.0f, 350.0f, 0.0f),
                    glm::vec3(4000.0f, 4000.0f, 1.0f),
                    glm::quat(),
                    1.0f
            },
            0.5f,
            0.5f
    ));

    resourceManager.SetResource("beat_explosion", particleAnimation);
    resourceManager.SetResource("explosion", beatAnimation);
    resourceManager.SetResource("spark_explosion_version_1", sparkAnimationVersion1);
    resourceManager.SetResource("spark_explosion_version_2", sparkAnimationVersion2);
    resourceManager.SetResource("spark_explosion_version_3", sparkAnimationVersion3);

    ServiceManager::GetInstance().Send(new Message{
            MessageType::KILL_MAIN_MENU_MUSIC,
            nullptr
    });
}

void MainGame::Release() {
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

    ServiceManager::GetInstance().Send(new Message{
            CLEAR_WORKSPACE_OBJECTS,
            nullptr
    });

    ResourceManager::GetInstance().ReleaseResources();
}

void MainGame::_initializeResources(AAssetManager* assetManager, ResourceManager& resourceManager) {
    /*
     * Set resources that are being used
     */
    resourceManager.SetResource("main_game_touch_area_up",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "touch_area_up.png"));
    resourceManager.SetResource("main_game_touch_area_down",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "touch_area_down.png"));
    resourceManager.SetResource("main_game_lane",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "lane.png"));
    resourceManager.SetResource("main_game_font_numbers",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "font_numbers.png"));
    resourceManager.SetResource("workspace_explosion",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "explosion.png"));
    resourceManager.SetResource("workspace_beat_explosion",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "beat_explosion.png"));
    resourceManager.SetResource("workspace_spark_explosion_version_1",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "sparks_explosion_01.png"));
    resourceManager.SetResource("workspace_spark_explosion_version_2",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "sparks_explosion_02.png"));
    resourceManager.SetResource("workspace_spark_explosion_version_3",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "sparks_explosion_03.png"));
    resourceManager.SetResource("tap_beat",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "beat.png"));
    resourceManager.SetResource("hold_beat_down",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "hold_beat_down.png"));
    resourceManager.SetResource("hold_beat_middle",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "hold_beat_middle.png"));
    resourceManager.SetResource("hold_beat_up",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "hold_beat_up.png"));
    resourceManager.SetResource("hold_beat_up_tail",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "hold_beat_up_tail.png"));
    resourceManager.SetResource("hold_beat_down_tail",
                                ResourceManager::CreateTextureObjectFromAsset(assetManager,
                                                                              "hold_beat_down_tail.png"));
}
