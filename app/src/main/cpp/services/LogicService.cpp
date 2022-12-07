//
// Created by michelle on 25/04/18.
//

#include "LogicService.h"

LogicService::LogicService() :
        Service(),
        _levelScore(new LevelScore()),
        _beatTexture(nullptr) {
    ServiceManager::GetInstance().GetObservable()->AddObserver(_observer);

    _hitStrings[HitType::MISS] = std::make_pair("Missed", 0);
    _hitStrings[HitType::PERFECT] = std::make_pair("Perfect", 100);
    _hitStrings[HitType::GOOD] = std::make_pair("Good", 50);
    _hitStrings[HitType::GREAT] = std::make_pair("Great", 75);
    _hitStrings[HitType::BAD] = std::make_pair("Bad", 0);
    _hitStrings[HitType::NO_BEAT] = std::make_pair("No beat?", 0);
}

LogicService::~LogicService() {
    if (_level != nullptr) {
        _level = nullptr;
    }

    if (_levelScore != nullptr) {
        delete (_levelScore);
        _levelScore = nullptr;
    }
}

void LogicService::Listener(Message* message) {
    switch (message->type) {
        case MessageType::ON_AUDIO_POSITION_UPDATE: {
            _onAudioPositionUpdate(message);
            break;
        }
        case MessageType::ON_BUTTON_PRESS: {
            LaneSide buttonSide = *(static_cast<LaneSide*>(message->pointer));
            Input* input = new Input{0,
                                     InputType::DOWN,
                                     glm::vec2(),
                                     glm::vec2()
            };
            _onInput(input, buttonSide);
            delete input;
            break;
        }
        case MessageType::ON_BUTTON_RELEASE: {
            LaneSide buttonSide = *(static_cast<LaneSide*>(message->pointer));
            Input* input = new Input{0,
                                     InputType::UP,
                                     glm::vec2(),
                                     glm::vec2()
            };
            _onInput(input, buttonSide);
            delete input;
            break;
        }
        case MessageType::LEVEL_FINISHED: {
            _levelFinish();
            break;
        }
        case MessageType::CREATE_BUILDENVIRONMENT: {
            _assetManager = static_cast<System*>(message->pointer)->assetManager;
            _nativeActivity = static_cast<System*>(message->pointer)->nativeActivity;
            break;
        }
        case MessageType::LOAD_GAME: {
            _currentLevelPath = *(static_cast<std::string*>(message->pointer));
            _loadGame();
            _initLevelScore(static_cast<std::string*>(message->pointer));
            break;
        }
        default: {
            break;
        }
    }
}

void LogicService::_onInput(Input* input, LaneSide laneSide) {

    /*
     * Get next screenBeat, if none then return
     */
    ScreenBeat* screenBeat = _getNextScreenBeat(laneSide);
    if (screenBeat == nullptr) return;

    HitType score = _handleScreenBeat(screenBeat, input);

    /*
     * Update score and combo
     */
    switch (score) {
        case HitType::NO_BEAT: {
            return;
        }
        case HitType::MISS:
        case HitType::BAD: {
            _updateMiss(score);
            break;
        };
        default : {
            _updateHit(score);
            _sendExplosionMessage(laneSide == LaneSide::RIGHT);
            break;
        }
    }

    /*
     * Update score and combo counters on screen
     */
    _sendHitMessage(score);
    _sendScoreMessage();
    _sendAddScoreMessage();
    _sendComboMessage();
}

ScreenBeat* LogicService::_getNextScreenBeat(LaneSide buttonSide) {
    ScreenBeat* screenBeat = nullptr;
    float smallestDifference = MAX_DISTANCE;

    for (auto it = _screenBeats.begin(); it != _screenBeats.end(); ++it) {
        float difference = abs((*it)->GetBeatPosition()) - _audioPosition;

        if (buttonSide == (*it)->GetLaneSide() && difference < smallestDifference) {
            screenBeat = (*it);
            smallestDifference = difference;
        }
    }
    return screenBeat;
}

HitType LogicService::_handleScreenBeat(ScreenBeat* screenBeat, Input* input) {
    HitType score = NO_BEAT;

    switch (screenBeat->GetBeatType()) {
        case TAPBEAT: {
            /*
             * If next screenBeat is a TAP check for DOWN input
             */
            if (input->type == InputType::DOWN) {
                score = _hitHandler->Handle(_audioPosition, screenBeat->GetBeatPosition());
                _popBeat(screenBeat);
            }
            break;
        }
        case HOLDBEAT: {
            if (input->type == InputType::DOWN) {
                score = _hitHandler->Handle(_audioPosition, screenBeat->GetBeatPosition());
                screenBeat->SetBeatPressed(true);
                if (score == HitType::MISS) {
                    _popBeat(screenBeat);
                    screenBeat->SetBeatPressed(false);
                }
            } else if (input->type == InputType::UP) {
                if (screenBeat->GetBeatPressed()) {
                    score = _hitHandler->Handle(_audioPosition, (screenBeat->GetBeatPosition() +
                                                                 screenBeat->GetBeatDuration()));
                    _popBeat(screenBeat);
                    screenBeat->SetBeatPressed(false);
                }
            }
            break;
        }
        default:
            break;
    }

    return score;
}

void LogicService::_updateHit(HitType score) {
    _sendParticleAnimationHit();

    _levelScore->combo++;
    _levelScore->comboScore += _hitStrings[score].second;
    if (_levelScore->combo % _moduloModifier == 0) {
        _levelScore->multiplier += 1.0f;
        _moduloModifier += _moduloModifier;
    }
    _levelScore->amounts[score]++;

    if (_levelScore->hits < MAX_HITS)
        _levelScore->hits++;
    _levelScore->accuracy = static_cast<float>(_levelScore->hits) / MAX_HITS;
    ServiceManager::GetInstance().Send(new Message{
            MessageType::PLAY_AUDIO_BEAT_HIT, NULL
    });
}

void LogicService::_updateMiss(HitType score) {
    _levelScore->score += _levelScore->comboScore * _levelScore->multiplier;
    if (_levelScore->combo > _levelScore->highestCombo)
        _levelScore->highestCombo = _levelScore->combo;
    _levelScore->combo = 0;
    _levelScore->comboScore = 0;
    _levelScore->multiplier = 1;

    _levelScore->amounts[score]++;

    if (_levelScore->hits > 0) _levelScore->hits--;
    _levelScore->accuracy = static_cast<float>(_levelScore->hits) / MAX_HITS;
    _moduloModifier = 3;

    ServiceManager::GetInstance().Send(new Message{
            MessageType::PLAY_AUDIO_BEAT_MISS, NULL
    });
}

void LogicService::_loadLevel(const char* levelPath) {
    if (_assetManager == nullptr) return;

    _level = LevelFactory::GetInstance().Load(_assetManager, levelPath);
    if (_level != nullptr) {
        _hitHandler = new HitHandler();
        _buildBeatQueue();

        _lastBeatMilliSeconds = 0;
        _milliSecondsPerBeat = 1000.0f / (static_cast<float>(_level->levelHeader.bpm) / 60.0f);
        _particleSystem = new ParticleSystem();

        ServiceManager::GetInstance().Send(new Message{
                ADD_WORKSPACE_OBJECT,
                _particleSystem
        });
    }
}

void LogicService::_buildBeatQueue() {
    if (_level == nullptr) return;
    _beatQueue.empty();

    for (int i = 0; i < _level->levelHeader.numberOfBeats; i++) {
        _beatQueue.push(&(_level->beatArray[i]));
    }

    _totalBeats = _beatQueue.size();
}

void LogicService::_tick() {
    _addProximityBeats();

    _updateProximityBeats();

    _removeProximityBeats();

    _updateSceneColor();

    _sendParticleAnimationBeat();
}

void LogicService::_addProximityBeats() {

    while (true) {
        Beat* beat = _beatQueue.front();
        if (beat == nullptr) return;
        /*
         * Position Beat on the correct side
         */
        LaneSide laneSide = beat->lane == 0x00 ? LaneSide::LEFT : LaneSide::RIGHT;
        float xPositionMultipier = beat->lane == 0x00 ? 0.18f : 0.82f;

        if (beat->position - _audioPosition < 1000) {
            _addBeat(beat,
                     laneSide,
                     static_cast<short>(Properties.WIDTH * xPositionMultipier),
                     static_cast<short>(Properties.HEIGHT * 0.8f));

            _beatQueue.pop();

            /*
             * Will exit when no screenBeat is added
             */
        } else return;
    }
}

void LogicService::_updateProximityBeats() {

    for (auto beatIt = _screenBeats.begin(); beatIt != _screenBeats.end(); ++beatIt) {
        (*beatIt)->Update(_audioPosition);
    }
}

void LogicService::_removeProximityBeats() {

    int removedBeats = 0;
    for (auto beatIt = _screenBeats.rbegin(); beatIt != _screenBeats.rend(); ++beatIt) {
        if ((*beatIt)->GetBeatEnd() - _audioPosition < -400) {
            _popBeat(*beatIt);
            _updateMiss(HitType::MISS);
            _sendHitMessage(HitType::MISS);

            removedBeats++;
        }
    }

    if (removedBeats > 0) {
        _sendScoreMessage();
        _sendAddScoreMessage();
        _sendComboMessage();
    }
}

void LogicService::_addBeat(Beat* beat, LaneSide laneSide, short x, short y) {
    if (beat->duration <= 100) {
        TapBeat* tapBeat = new TapBeat(*beat, laneSide, x, y);
        _screenBeats.push_back(tapBeat);
    } else {
        HoldBeat* holdBeatDown = new HoldBeat(*beat, laneSide, x, y);
        _screenBeats.push_back(holdBeatDown);
    }
}

void LogicService::_popBeat(ScreenBeat* screenBeat) {
    screenBeat->ClearBeat();

    _screenBeats.erase(std::remove(_screenBeats.begin(), _screenBeats.end(), screenBeat),
                       _screenBeats.end());
    delete screenBeat;
}

void LogicService::_updateSceneColor() const {
    glm::vec3 color = glm::vec3(
            2.0f - _levelScore->accuracy * 2,
            _levelScore->accuracy * 2,
            0.0f
    );

    ServiceManager::GetInstance().Send(new Message{
            SET_SCENE_COLOR,
            &color
    });
}

void LogicService::_sendScoreMessage() {
    std::string scoreString = std::to_string(_levelScore->score);

    StringRenderData srdScore{"score", "white-font.ini",
                              scoreString.c_str(),
                              0.25f, 50, 10, StringAlignment::ALIGN_LEFT, 0.0f};
    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            &srdScore
    });

}

void LogicService::_sendComboMessage() {
    std::string comboString = std::to_string(_levelScore->combo) + "X";
    StringRenderData srdCombo{"combo", "white-font.ini", comboString.c_str(), 0.4f, 950, 255,
                              StringAlignment::ALIGN_RIGHT,
                              0.0f};
    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            &srdCombo
    });
}

void LogicService::_sendHitMessage(HitType hitType) {
    std::string hit = _hitStrings[hitType].first;

    StringRenderData srdHit{"hit-message", "abc-font.ini", hit.c_str(), 0.3f, 640, 590,
                            StringAlignment::ALIGN_CENTER, 0.0f};
    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            &srdHit
    });
}

void LogicService::_sendExplosionMessage(bool lane) {
    ServiceManager::GetInstance().Send(new Message{
            MessageType::ADD_WORKSPACE_OBJECT,
            new BeatExplosion(lane, _audioPosition)
    });
}

void LogicService::_sendAddScoreMessage() {
    std::string scoreString = "";
    if (_levelScore->comboScore >= 1) {
        scoreString = ";" + std::to_string(_levelScore->comboScore) + "&X&" +
                      std::to_string((short) _levelScore->multiplier);
    }
    StringRenderData srdScore{"add-score", "white-font.ini",
                              scoreString.c_str(),
                              0.3f, 13, 50, StringAlignment::ALIGN_LEFT, 0.0f};
    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            &srdScore
    });
}

void LogicService::_sendParticleAnimationHit() {

    _particleSystem->Play(ResourceManager::GetInstance().GetParticleAnimation("explosion"),
                          static_cast<unsigned long>(_audioPosition));

    int randomIndex = rand() % 3;

    switch (randomIndex) {
        case 0:
            _particleSystem->Play(ResourceManager::GetInstance().GetParticleAnimation(
                    "spark_explosion_version_1"),
                                  static_cast<unsigned long>(_audioPosition));

            break;
        case 1:
            _particleSystem->Play(ResourceManager::GetInstance().GetParticleAnimation(
                    "spark_explosion_version_2"),
                                  static_cast<unsigned long>(_audioPosition));

            break;
        case 2:
            _particleSystem->Play(ResourceManager::GetInstance().GetParticleAnimation(
                    "spark_explosion_version_3"),
                                  static_cast<unsigned long>(_audioPosition));

            break;
    }
}

void LogicService::_sendParticleAnimationBeat() {
    //Check for beats
    if (_audioPosition > _lastBeatMilliSeconds + _milliSecondsPerBeat) {
        _lastBeatMilliSeconds += static_cast<long>(_milliSecondsPerBeat);

        _particleSystem->Play(ResourceManager::GetInstance().GetParticleAnimation("beat_explosion"),
                              static_cast<unsigned long>(_audioPosition));
    }

}

void LogicService::_onAudioPositionUpdate(Message* message) {
    AudioPlayer* player = (AudioPlayer*) message->pointer;
    if (player->IsPlaying()) {
        _audioPosition = (float) player->GetPosition();
        _tick();
    } else {
        ServiceManager::GetInstance().Send(new Message{
                MessageType::LEVEL_FINISHED,
                _levelScore
        });
        ServiceManager::GetInstance().Send(new Message{
                MessageType::SET_UISCENE,
                new ResultScreen(0, 0, _levelScore)
        });
        ServiceManager::GetInstance().Send(new Message{
                MessageType::SWITCH_SCREEN,
                NULL
        });
    }
}

void LogicService::_loadGame() {
    _loadLevel(_currentLevelPath.c_str());

    // Load fonts to prevent lag spikes further on
    SpriteString blueFont(_assetManager, "white-font.ini", "1");
    SpriteString greenFont(_assetManager, "abc-font.ini", "1");

    // Request the background track to be loaded
    ServiceManager::GetInstance().Send(new Message{
            MessageType::LOAD_BACKGROUND_TRACK,
            _level->levelHeader.songName
    });
}

void LogicService::_initLevelScore(std::string* path) {
    _levelScore = new LevelScore();
    _levelScore->level = *path;
    _levelScore->hits = MAX_HITS;
    _levelScore->combo = 0;
    _levelScore->comboScore = 0;
    _levelScore->multiplier = 1;
    _levelScore->amounts[HitType::PERFECT] = 0;
    _levelScore->amounts[HitType::GREAT] = 0;
    _levelScore->amounts[HitType::GOOD] = 0;
    _levelScore->amounts[HitType::BAD] = 0;
    _levelScore->amounts[HitType::MISS] = 0;

    _moduloModifier = 3;
}

void LogicService::_levelFinish() {
    _levelScore->score += _levelScore->comboScore * _levelScore->multiplier;
    if (_levelScore->combo > _levelScore->highestCombo)
        _levelScore->highestCombo = _levelScore->combo;


    _levelScore->accuracy =
            (_totalBeats - _levelScore->amounts[HitType::MISS]) / _totalBeats * 100;


    _levelScore->highscore = HighscoreFactory::GetInstance().LoadHighScore(
            _nativeActivity, _currentLevelPath);

    if (_levelScore->score > _levelScore->highscore) {
        _levelScore->highscore = _levelScore->score;
    }

    _levelScore->placement = HighscoreFactory::GetInstance().Write(
            _nativeActivity, _levelScore->score, _currentLevelPath);
}
