//
// Created by patri on 5/24/2018.
//

#include "WorkspaceService.h"

WorkspaceService::WorkspaceService() :
        Service() {
    ServiceManager::GetInstance().GetObservable()->AddObserver(_observer);
}

void WorkspaceService::Listener(Message* message) {
    switch (message->type) {
        case MessageType::ON_AUDIO_POSITION_UPDATE: {
            _updateWorkspaceObject(static_cast<AudioPlayer*>(message->pointer));
            break;
        }
        case MessageType::ADD_WORKSPACE_OBJECT: {
            _addWorkspaceObject(static_cast<WorkspaceObject*>(message->pointer));
            break;
        }
        case MessageType::REMOVE_WORKSPACE_OBJECT: {
            _removeWorkspaceObject(static_cast<WorkspaceObject*>(message->pointer));
            break;
        }
        case MessageType::CLEAR_WORKSPACE_OBJECTS: {
            _clearWorkspaceObjects();
            break;
        }
        default:
            break;
    }
}

void WorkspaceService::_updateWorkspaceObject(AudioPlayer* audioPlayer) {
    WorkspaceObject* prevWorkspaceObject = nullptr;

    std::vector<WorkspaceObject*> rubbish;

    for (auto workspaceObjectIt = _workspaceObjects.begin();
         workspaceObjectIt != _workspaceObjects.end(); ++workspaceObjectIt) {
        (*workspaceObjectIt)->Update(audioPlayer);
        if (prevWorkspaceObject != nullptr) {
            if (prevWorkspaceObject->ShouldBeDeleted()) {
                rubbish.push_back(prevWorkspaceObject);
            }
        }
        prevWorkspaceObject = (*workspaceObjectIt);
    }

    for (auto it = rubbish.begin(); it != rubbish.end(); it++) {
        _removeWorkspaceObject(*it);
    }
}

void WorkspaceService::_addWorkspaceObject(WorkspaceObject* workspaceObject) {
    _workspaceObjects.push_back(workspaceObject);
    workspaceObject->Initialize();
}

void WorkspaceService::_removeWorkspaceObject(WorkspaceObject* workspaceObject) {
    _workspaceObjects.erase(
            std::remove(_workspaceObjects.begin(), _workspaceObjects.end(), workspaceObject),
            _workspaceObjects.end());
    workspaceObject->Clear();
    if (workspaceObject->ShouldBeDeleted()) {
        delete workspaceObject;
    }
}

void WorkspaceService::_clearWorkspaceObjects() {
    for (auto it = _workspaceObjects.begin(); it != _workspaceObjects.end(); it++) {
        (*it)->Clear();
        delete *it;
    }

    _workspaceObjects.clear();
}
