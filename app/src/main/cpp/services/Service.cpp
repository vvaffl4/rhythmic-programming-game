//
// Created by patrick on 4/19/2018.
// Reviewed and edited by maarten on 4/23/2018.
//

#include "Service.h"

Service::Service() : _observer(new Observer(this)) {}

Service::~Service() {
    if (_observer != nullptr) {
        delete _observer;
        _observer = nullptr;
    }
}

