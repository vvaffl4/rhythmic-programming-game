//
// Created by michelle on 25/04/18.
//

#include "AudioService.h"


AudioService::AudioService() : Service() {
    ServiceManager::GetInstance().GetObservable()->AddObserver(_observer);
}

AudioService::~AudioService() {

    _killAudioPlayer();
    _clearSFXPlayers();
    if (_assetManager != nullptr) _assetManager = nullptr;
}

void AudioService::Listener(Message* message) {
    switch (message->type) {
        case MessageType::ON_LOGIC_LOOP: {
            if (_good) {
                ServiceManager::GetInstance().Send(new Message{
                        MessageType::ON_AUDIO_POSITION_UPDATE,
                        _audioPlayer
                });
            }

            break;
        }
        case MessageType::PLAY_AUDIO_BEAT_MISS: {
            _createSFXPlayer(AudioClip::BEAT_MISS, "beat_miss.mp3");
            break;
        }
        case MessageType::PLAY_AUDIO_CONFIRM: {
            _createSFXPlayer(AudioClip::CONFIRM, "confirm.mp3");
            break;
        }

        case MessageType::PLAY_AUDIO_CANCEL: {
            _createSFXPlayer(AudioClip::CANCEL, "cancel.mp3");
            break;
        }

        case MessageType::PLAY_AUDIO_BEAT_HIT: {
            _createSFXPlayer(AudioClip::BEAT_HIT, "beat_hit.mp3");
            break;
        }
        case MessageType::ON_TERM_DISPLAY: {
            if (_audioPlayer != nullptr) _audioPlayer->Stop();
            break;
        }
        case MessageType::PLAY_AUDIO_MAIN_MENU_MUSIC: {
            _createSFXPlayer(AudioClip::MAIN_MENU_MUSIC, "Bog-Creatures-On-the-Move_Looping.mp3");
            break;
        }
        case MessageType::KILL_MAIN_MENU_MUSIC: {
            auto it = _sfxPlayers.find(AudioClip::MAIN_MENU_MUSIC);
            it->second->Stop();
            break;
        }
        case MessageType::LOAD_BACKGROUND_TRACK: {
            _createAudioPlayer(static_cast<char*>(message->pointer));
            break;
        }
        case MessageType::START_GAME: {
            _startAudioPlayer();
            break;
        }
        case MessageType::LEVEL_FINISHED: {
            _killAudioPlayer();
            break;
        }
        case MessageType::CREATE_BUILDENVIRONMENT: {
            _assetManager = static_cast<System*>(message->pointer)->assetManager;
            break;
        }

        default:
            break;
    }
}

void AudioService::_killAudioPlayer() {
    if (_audioPlayer != nullptr) {
        if (_audioPlayer->IsPlaying()) {
            _audioPlayer->Stop();
        }
        delete _audioPlayer;
        _audioPlayer = nullptr;
        _good = false;
    }
}

void AudioService::_createAudioPlayer(const char* filePath) {
    if (_assetManager == nullptr)
        return;

    _killAudioPlayer();
    _audioPlayer = new AudioPlayer();
    _good = _audioPlayer->CreateAssetAudioPlayer(_assetManager, filePath);
}

void AudioService::_startAudioPlayer() {
    if (_good) _audioPlayer->Play();
}

void AudioService::_createSFXPlayer(AudioClip audioClip, const char* filePath) {
    auto it = _sfxPlayers.find(audioClip);
    if (it == _sfxPlayers.end()) {
        AudioPlayer* audioPlayer = new AudioPlayer();
        audioPlayer->CreateAssetAudioPlayer(_assetManager, filePath);
        if (audioClip == AudioClip::MAIN_MENU_MUSIC) {
            audioPlayer->Loop();
        }
        _sfxPlayers.emplace(audioClip, audioPlayer);
        audioPlayer->Play();
    } else {
        if (it->first != AudioClip::MAIN_MENU_MUSIC) {
            it->second->Stop();
            it->second->Play();
        }
        if (it->second->IsPlaying() != true) {
            it->second->Play();
        }
    }
}

void AudioService::_clearSFXPlayers() {
    for (auto player = _sfxPlayers.begin(); player != _sfxPlayers.end(); ++player) {
        if (player->second->IsPlaying()) {
            player->second->Stop();
        }
        delete (player->second);
    }
    _sfxPlayers.clear();
}
