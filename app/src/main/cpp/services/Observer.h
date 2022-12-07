//
// Created by patrick on 4/23/2018.
// Reviewed and edited by maarten on 4/23/2018.
//

#ifndef RHYTHMICPROGRAMMING_OBSERVER_H
#define RHYTHMICPROGRAMMING_OBSERVER_H

class Service;

#include "Service.h"

struct Message;

class Observer {
private:
    Service* _service = nullptr;
public:
    Observer(Service* service);

    ~Observer();

    void OnMessage(Message* message);
};


#endif //RHYTHMICPROGRAMMING_OBSERVER_H
