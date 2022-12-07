//
// Created by michelle on 25/05/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_INSTANCETRACKER_H
#define RHYTHMIC_PROGRAMMING_GAME_INSTANCETRACKER_H

#include <android/log.h>
#include <string>
#include <algorithm>
#include <map>

#define INSTANCE_TRACKER_LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "InstanceTracker", __VA_ARGS__))

class InstanceTracker {
private:
    std::map<std::string, int> _tracker;

    InstanceTracker() {}

public:
    InstanceTracker(InstanceTracker const&) = delete;

    void operator=(InstanceTracker const&) = delete;

    static InstanceTracker& GetInstance() {
        static InstanceTracker instance;
        return instance;
    }

    void Track(const std::string& key);

    void Untrack(const std::string& key);
};


#endif //RHYTHMIC_PROGRAMMING_GAME_INSTANCETRACKER_H
