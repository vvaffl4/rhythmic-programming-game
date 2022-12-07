//
// Created by patrick on 4/19/2018.
// Reviewed and edited by maarten on 4/23/2018.
//

#ifndef RHYTHMICPROGRAMMING_INPUTOBSERVER_H
#define RHYTHMICPROGRAMMING_INPUTOBSERVER_H

#include <vector>
#include "Service.h"
#include "Observable.h"
#include "../input/InputHandler.h"
#include "AudioService.h"

/*
 * MessageType Name policy
 *
 * Action: ON, CREATE, ADD, REMOVE, DELETE, BEFORE, AFTER, ASSIGN, DEASSIGN
 * Event:
 */

enum MessageType {
    INPUT,
    ADD_OBJECT2D,
    REMOVE_OBJECT2D,
    SET_UISCENE,
    CREATE_BUILDENVIRONMENT,
    AFTER_BEATQUEUE_INIT,
    LOAD_GAME,
    START_GAME,
    ON_BUTTON_PRESS,
    ON_BUTTON_RELEASE,
    ON_AUDIO_POSITION_UPDATE,
    ON_LOGIC_LOOP,
    ON_TERM_DISPLAY,
    ON_INIT_DISPLAY,
    LEVEL_FINISHED,
    SWITCH_SCREEN,
    RENDER_STRING,
    UNRENDER_STRING,
    KILL_MAIN_MENU_MUSIC,

    PLAY_AUDIO_CONFIRM,
    PLAY_AUDIO_CANCEL,
    PLAY_AUDIO_BEAT_HIT,
    PLAY_AUDIO_BEAT_MISS,
    PLAY_AUDIO_MAIN_MENU_MUSIC,
    LOAD_BACKGROUND_TRACK,
    ADD_BACKGROUND_OBJECT2D,
    REMOVE_BACKGROUND_OBJECT2D,
    UNRENDER_ALL_STRINGS,
    ADD_WORKSPACE_OBJECT,
    REMOVE_WORKSPACE_OBJECT,
    CLEAR_WORKSPACE_OBJECTS,
    RENDER_FRAME,
    SET_SCENE_COLOR
};

struct Message {
    MessageType type;
    void* pointer;
};

class ServiceManager {
private:
    Observable* _observable = nullptr;

    std::vector<Service*> _registry;

    ServiceManager();

    void _register(Service* service);

public:
    ServiceManager(ServiceManager const&) = delete;

    void operator=(ServiceManager const&) = delete;

    static ServiceManager& GetInstance() {
        static ServiceManager serviceManager;
        return serviceManager;
    };

    void Send(Message* message);

    Observable* GetObservable();

    void CreateServices();

    void DestroyServices();
};


#endif //RHYTHMICPROGRAMMING_INPUTOBSERVER_H
