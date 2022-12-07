//
// Created by patrick on 4/23/2018.
// Reviewed and edited by maarten on 4/23/2018.
//

#include "Observer.h"

Observer::Observer(Service* service) : _service(service) {}

void Observer::OnMessage(Message* message) {
    if (_service == nullptr) return;
    _service->Listener(message);
}

Observer::~Observer() {
    _service = nullptr;
}