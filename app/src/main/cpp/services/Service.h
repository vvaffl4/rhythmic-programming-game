//
// Created by patrick on 4/19/2018.
// Reviewed and edited by maarten on 4/23/2018.
//

#ifndef RHYTHMICPROGRAMMING_SERVICE_H
#define RHYTHMICPROGRAMMING_SERVICE_H

class Observer;

#include "Observer.h"

class ServiceManager;

struct Message;

class Service {
protected:
    Observer* _observer = nullptr;
public:
    Service();

    virtual ~Service();

    virtual void Listener(Message* message) = 0;
};


#endif //RHYTHMICPROGRAMMING_SERVICE_H
