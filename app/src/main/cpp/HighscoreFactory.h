//
// Created by jaron on 29-5-2018.
//

#ifndef REPO_HIGHSCOREFACTORY_H
#define REPO_HIGHSCOREFACTORY_H

#include <sys/stat.h>
#include <android/log.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <android/native_activity.h>
#include <vector>
#include <algorithm>

#include "ScoreStructs.cpp"

class HighscoreFactory {
private:
    int _levelCount = 1;

    HighscoreFactory() {}

    std::string _levelNameToPath(ANativeActivity* nativeActivity, std::string& levelName);

public:

    HighscoreFactory(HighscoreFactory const&) = delete;

    void operator=(HighscoreFactory const&) = delete;

    static HighscoreFactory& GetInstance() {
        static HighscoreFactory instance;
        return instance;
    }

    LevelHighscore Load(ANativeActivity* nativeActivity, std::string& levelName);

    int LoadHighScore(ANativeActivity* nativeActivity, std::string& levelName);

    int Write(ANativeActivity* nativeActivity, int score, std::string& levelName);
};


#endif //REPO_HIGHSCOREFACTORY_H
