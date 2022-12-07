//
// Created by patrick on 4/19/2018.
// Reviewed and edited by maarten on 4/23/2018.
//

#include "ServiceManager.h"
#include "UIService.h"
#include "RenderService.h"
#include "LogicService.h"
#include "AudioService.h"
#include "WorkspaceService.h"

ServiceManager::ServiceManager() {
}

void ServiceManager::Send(Message* message) {
    _observable->Broadcast(message);
}

Observable* ServiceManager::GetObservable() {
    return _observable;
}

void ServiceManager::CreateServices() {
    if (_registry.size() > 0) return;

    _observable = new Observable();

    _register(new UIService());
    _register(new RenderService());
    _register(new AudioService());
    _register(new LogicService());
    _register(new WorkspaceService());
}

void ServiceManager::DestroyServices() {
    for (auto it = _registry.begin(); it != _registry.end(); it++) {
        delete *it;
    }

    _registry.clear();
    if (_observable != nullptr) {
        delete _observable;
        _observable = nullptr;
    }
}

void ServiceManager::_register(Service* service) {
    _registry.push_back(service);
}
