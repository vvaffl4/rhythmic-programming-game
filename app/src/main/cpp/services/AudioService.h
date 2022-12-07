//
// Created by michelle on 25/04/18.
//

#ifndef RYTHMIC_PROGRAMMING_AUDIOSERVICE_H
#define RYTHMIC_PROGRAMMING_AUDIOSERVICE_H


#include "Service.h"
#include "ServiceManager.h"
#include "../AudioPlayer.h"
#include <map>

enum AudioClip {
    CONFIRM,
    CANCEL,
    BEAT_HIT,
    BEAT_MISS,
    MAIN_MENU_MUSIC
};

class AudioService : public Service {
private:
    AudioPlayer* _audioPlayer = nullptr;
    AAssetManager* _assetManager = nullptr;
    std::map<AudioClip, AudioPlayer*> _sfxPlayers;
    bool _good = false;

    void _killAudioPlayer();

    void _createAudioPlayer(const char filePath[15]);

    void _createSFXPlayer(AudioClip, const char filePath[15]);

    void _clearSFXPlayers();

    void _startAudioPlayer();

public:
    AudioService();

    ~AudioService();

    void Listener(Message* message) override;
};


#endif //RYTHMIC_PROGRAMMING_AUDIOSERVICE_H
