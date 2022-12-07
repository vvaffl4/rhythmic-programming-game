//
// Created by patrick on 4/23/2018.
// Reviewed and edited by maarten on 4/23/2018.
//

#include "Observable.h"

Observable::Observable() {

}

void Observable::Broadcast(Message* message) {
    for (auto observerIt = _observers.begin(); observerIt != _observers.end(); ++observerIt) {
        (*observerIt)->OnMessage(message);
    }
    delete message;
}

void Observable::AddObserver(Observer* observer) {
    _observers.push_back(observer);
}

Observable::~Observable() {
    _observers.clear();
}
