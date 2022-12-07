//
// Created by patri on 4/17/2018.
//

#ifndef NATIVE_ACTIVITY_AUDIOPLAYER_H
#define NATIVE_ACTIVITY_AUDIOPLAYER_H

#include <string>

// For native audio
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// For native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class AudioPlayer {
private:
    SLObjectItf _outputMixObject = nullptr;
    SLObjectItf _audioEngineObject = nullptr;
    SLEngineItf _audioEngine;
    SLObjectItf _audioPlayerObject = nullptr;
    SLPlayItf _audioPlayer;
    SLSeekItf _audioPlayerSeek;
    SLMuteSoloItf _audioPlayerMuteSolo;
    SLVolumeItf _audioPlayerVolume;

public:
    AudioPlayer();

    ~AudioPlayer();

    bool CreateAssetAudioPlayer(AAssetManager* assetManager, const std::string& path);

    bool Play();

    bool Stop();

    bool SetPosition(const SLmillisecond& position);

    SLmillisecond GetPosition();

    bool IsPlaying();

    static void audioPlayerCallback(SLPlayItf audioPlayer, void* context, SLuint32 event);

    bool Loop();
};


#endif //NATIVE_ACTIVITY_AUDIOPLAYER_H
