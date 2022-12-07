//
// Created by patrick on 4/17/2018.
//

#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() {
    SLresult result;

    // Create engine
    result = slCreateEngine(&_audioEngineObject, 0, NULL, 0, NULL, NULL);
    if (result != SL_RESULT_SUCCESS)
        return;
    (void) result;

    // Realize engine
    result = (*_audioEngineObject)->Realize(_audioEngineObject, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS)
        return;
    (void) result;

    // Get engine interface, to create other objects (HIGHLY NEEDED)
    result = (*_audioEngineObject)->GetInterface(_audioEngineObject, SL_IID_ENGINE, &_audioEngine);
    if (result != SL_RESULT_SUCCESS)
        return;
    (void) result;

    // Create output mix, (with environmental reverb specified as a non-required interface)
    result = (*_audioEngine)->CreateOutputMix(_audioEngine, &_outputMixObject, 0, NULL, NULL);
    if (result != SL_RESULT_SUCCESS)
        return;
    (void) result;

    // Realize the output mix
    result = (*_outputMixObject)->Realize(_outputMixObject, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS)
        return;
    (void) result;
}

void AudioPlayer::audioPlayerCallback(SLPlayItf audioPlayer, void* context, SLuint32 event) {
    static_cast<AudioPlayer*>(context)->Stop();
}

AudioPlayer::~AudioPlayer() {

    if (_audioPlayerObject != nullptr) {
        (*_audioPlayerObject)->Destroy(_audioPlayerObject);
        _audioEngineObject = nullptr;
    }

    if (_outputMixObject != nullptr) {
        (*_outputMixObject)->Destroy(_outputMixObject);
        _outputMixObject = nullptr;
    }

    if (_audioEngineObject != nullptr) {
        (*_audioEngineObject)->Destroy(_audioEngineObject);
        _audioEngineObject = nullptr;
    }
}

bool AudioPlayer::CreateAssetAudioPlayer(AAssetManager* assetManager, const std::string& path) {

    AAsset* asset = AAssetManager_open(assetManager, path.c_str(), AASSET_MODE_UNKNOWN);

    if (asset == NULL)
        return false;

    // Get file descriptor
    off_t start;
    off_t length;
    int fileDescriptor = AAsset_openFileDescriptor(asset, &start, &length);
    AAsset_close(asset);

    // Configure audio source
    SLDataLocator_AndroidFD locatorFileDescriptor = {
            SL_DATALOCATOR_ANDROIDFD,
            fileDescriptor,
            start,
            length};
    SLDataFormat_MIME formatMime = {SL_DATAFORMAT_MIME, NULL,
                                    SL_CONTAINERTYPE_UNSPECIFIED}; //SL_CONTAINERTYPE_UNSPECIFIED
    SLDataSource audioSource = {&locatorFileDescriptor, &formatMime};

    // Configure audio sink
    SLDataLocator_OutputMix locatorOutputMix = {SL_DATALOCATOR_OUTPUTMIX, _outputMixObject};
    SLDataSink audioSink = {&locatorOutputMix, NULL};

    SLresult result;

    // Create audio player
    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    result = (*_audioEngine)->CreateAudioPlayer(
            _audioEngine,
            &_audioPlayerObject,
            &audioSource,
            &audioSink,
            3,
            ids,
            req);
    if (result != SL_RESULT_SUCCESS)
        return false;
    (void) result;

    // Realize audio player
    result = (*_audioPlayerObject)->Realize(_audioPlayerObject, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS)
        return false;
    (void) result;

    // Get Play interface
    result = (*_audioPlayerObject)->GetInterface(_audioPlayerObject, SL_IID_PLAY, &_audioPlayer);
    if (result != SL_RESULT_SUCCESS)
        return false;
    (void) result;

    // Register callback on the audioPlayer
    result = (*_audioPlayer)->RegisterCallback(_audioPlayer, audioPlayerCallback, this);
    if (result != SL_RESULT_SUCCESS)
        return false;
    (void) result;

    // Mask only the end of the song event
    result = (*_audioPlayer)->SetCallbackEventsMask(_audioPlayer, SL_PLAYEVENT_HEADATEND);
    if (result != SL_RESULT_SUCCESS)
        return false;
    (void) result;

    // Get the seek interface
    result = (*_audioPlayerObject)->GetInterface(_audioPlayerObject, SL_IID_SEEK,
                                                 &_audioPlayerSeek);
    if (result != SL_RESULT_SUCCESS)
        return false;
    (void) result;

    // Get the Mute/solo interface
    result = (*_audioPlayerObject)->GetInterface(_audioPlayerObject, SL_IID_MUTESOLO,
                                                 &_audioPlayerMuteSolo);
    if (result != SL_RESULT_SUCCESS)
        return false;
    (void) result;

    // Get the volume interface
    result = (*_audioPlayerObject)->GetInterface(_audioPlayerObject, SL_IID_VOLUME,
                                                 &_audioPlayerVolume);
    if (result != SL_RESULT_SUCCESS)
        return false;
    (void) result;

    // Enable whole file looping
    return result == SL_RESULT_SUCCESS;
}

bool AudioPlayer::Play() {
    if (_audioPlayer != NULL)
        return (*_audioPlayer)->SetPlayState(_audioPlayer, SL_PLAYSTATE_PLAYING) ==
               SL_RESULT_SUCCESS;

    return false;
}

bool AudioPlayer::Loop() {
    if (_audioPlayer != NULL)
        return (*_audioPlayerSeek)->SetLoop(_audioPlayerSeek, SL_BOOLEAN_TRUE, 0,
                                            SL_TIME_UNKNOWN) == SL_RESULT_SUCCESS;

    return false;
}

bool AudioPlayer::Stop() {
    if (_audioPlayer != NULL) {
        return (*_audioPlayer)->SetPlayState(_audioPlayer, SL_PLAYSTATE_STOPPED) ==
               SL_RESULT_SUCCESS;
    }

    return false;
}

SLmillisecond AudioPlayer::GetPosition() {
    if (_audioPlayer != NULL) {
        SLresult result;

        SLmillisecond position = NULL;

        result = (*_audioPlayer)->GetPosition(_audioPlayer, &position);
        if (result == SL_RESULT_SUCCESS)
            return position;
    }

    return (SLmillisecond) 0;
}

bool AudioPlayer::SetPosition(const SLmillisecond& position) {
    if (_audioPlayer != NULL) {
        return (*_audioPlayerSeek)->SetPosition(_audioPlayerSeek, position, SL_SEEKMODE_ACCURATE) ==
               SL_RESULT_SUCCESS;
    }
    return false;
}

bool AudioPlayer::IsPlaying() {
    if (_audioPlayer != NULL) {

        SLresult result;
        SLuint32 playState;
        result = (*_audioPlayer)->GetPlayState(_audioPlayer, &playState);
        if (result != SL_RESULT_SUCCESS)
            return false;
        (void) result;

        return playState == SL_PLAYSTATE_PLAYING;
    }

    return false;
}

