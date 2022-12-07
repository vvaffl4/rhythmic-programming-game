//
// Created by michelle on 25/05/18.
//

#include "InstanceTracker.h"

void InstanceTracker::Track(const std::string& key) {
    if (!_tracker[key]) {
        _tracker[key] = 1;
    } else {
        _tracker[key]++;
    }

    INSTANCE_TRACKER_LOGI("Instance %s now has %d instances", key.c_str(), _tracker[key]);
}

void InstanceTracker::Untrack(const std::string& key) {
    if (!_tracker[key]) {
        _tracker[key] = 0;
    } else {
        _tracker[key] = _tracker[key] - 1;
    }
    INSTANCE_TRACKER_LOGI("Instance %s now has %d instances", key.c_str(), _tracker[key]);
}
