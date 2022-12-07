//
// Created by patrick on 4/23/2018.
// Reviewed and edited by maarten on 4/23/2018.
//

#ifndef RHYTHMICPROGRAMMING_OBSERVABLE_H
#define RHYTHMICPROGRAMMING_OBSERVABLE_H

#include <vector>
#include "Observer.h"

struct Message;

class Observable {
private:
    std::vector<Observer*> _observers;
public:
    Observable();

    ~Observable();

    void Broadcast(Message* message);

    void AddObserver(Observer* observer);
};


#endif //RHYTHMICPROGRAMMING_OBSERVABLE_H
