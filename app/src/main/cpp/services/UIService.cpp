//
// Created by pw on 21-4-2018.
//

#include "UIService.h"

UIService::UIService() :
        Service(),
        _nextScene(nullptr),
        _scene(nullptr) {

    //Subscribe Observer to Observable of ServiceManager
    ServiceManager::GetInstance().GetObservable()->AddObserver(_observer);
}

void UIService::Listener(Message* message) {
    switch (message->type) {
        case MessageType::ON_LOGIC_LOOP: {
            double* deltaTime = static_cast<double*>(message->pointer);

            if (_scene != nullptr) {
                _scene->Update(*deltaTime);
            }
            break;
        }
        case MessageType::INPUT: {
            ProcessInput(static_cast<Input*>(message->pointer));
            break;
        }
        case MessageType::SET_UISCENE: {
            SetScene(static_cast<UIScene*>(message->pointer));
            break;
        }
        case MessageType::SWITCH_SCREEN: {
            SwitchScreen();
            break;
        }
        case MessageType::CREATE_BUILDENVIRONMENT: {
            _system = static_cast<System*>(message->pointer);
            break;
        }
    }
}

void UIService::SetScene(UIScene* scene) {
    _nextScene = scene;
    _sceneSwitched = true;
}

void UIService::SwitchScreen() {
    if (_scene != nullptr) {
        _scene->Release();
        delete _scene;
        _scene = nullptr;
    }

    if (_nextScene == nullptr) return;

    _scene = _nextScene;
    _scene->Initialize(_system->assetManager, _system->nativeActivity);
    _nextScene = nullptr;

    _sceneSwitched = false;
}

void UIService::ProcessInput(Input* input) {

    _scene->ProcessInput(input);

    if (_sceneSwitched) {
        SwitchScreen();
    }
}
