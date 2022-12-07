//
// Created by michelle on 25/04/18.
//

#ifndef RYTHMIC_PROGRAMMING_LOGICSERVICE_H
#define RYTHMIC_PROGRAMMING_LOGICSERVICE_H

class ScreenBeat;

#include "Service.h"
#include "ServiceManager.h"
#include "../input/InputHandler.h"
#include "../AudioPlayer.h"
#include "../LevelFactory.h"
#include "../HighscoreFactory.h"
#include "../input/HitHandler.h"
#include "../uiobjects/ScreenBeat.h"
#include "../uiobjects/TapBeat.h"
#include "../uiobjects/HoldBeat.h"
#include "../LaneSide.h"
#include "../sprite/StringRenderData.cpp"
#include "../sprite/SpriteString.h"
#include "../workspace/BeatExplosion.h"
#include "../ResourceManager.h"
#include "../properties.h"
#include "../screens/ResultScreen.h"
#include "../LevelScore.cpp"
#include "../particles/ParticleSystem.h"

#include <queue>
#include <vector>
#include <math.h>
#include <map>
#include <string>

class LogicService : public Service {
private:
    AAssetManager* _assetManager = nullptr;
    ANativeActivity* _nativeActivity = nullptr;
    Level* _level = nullptr;
    LevelScore* _levelScore = nullptr;
    HitHandler* _hitHandler = nullptr;
    Texture* _beatTexture = nullptr;
    std::queue<Beat*> _beatQueue;
    std::map<HitType, std::pair<const char*, int>> _hitStrings;
    std::vector<ScreenBeat*> _screenBeats;
    int _moduloModifier = 3;

    float _milliSecondsPerBeat;
    long _lastBeatMilliSeconds;
    ParticleSystem* _particleSystem;

    float _audioPosition = 0;
    float _totalBeats = 0;

    std::string _currentLevelPath;

    const int MAX_HITS = 10;
    const int MAX_DISTANCE = 800;

    void _onInput(Input* input, LaneSide laneSide);

    void _loadLevel(const char levelPath[16]);

    void _buildBeatQueue();

    void _tick();

    void _onAudioPositionUpdate(Message* message);

    void _loadGame();

    void _levelFinish();

    void _initLevelScore(std::string* path);

    void _addProximityBeats();

    void _updateProximityBeats();

    void _removeProximityBeats();

    void _addBeat(Beat* beat, LaneSide laneSide, short x, short y);

    void _popBeat(ScreenBeat* screenBeat);

    void _sendScoreMessage();

    void _sendComboMessage();

    void _sendHitMessage(HitType hitType);

    void _sendExplosionMessage(bool lane);

    void _sendAddScoreMessage();

    void _sendParticleAnimationBeat();

    void _sendParticleAnimationHit();

    void _updateSceneColor() const;

    void _updateMiss(HitType score);

    void _updateHit(HitType score);

    ScreenBeat* _getNextScreenBeat(LaneSide buttonSide);

    HitType _handleScreenBeat(ScreenBeat* screenBeat, Input* input);

public:
    LogicService();

    ~LogicService();

    void Listener(Message* message) override;

};


#endif //RYTHMIC_PROGRAMMING_LOGICSERVICE_H
