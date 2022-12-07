//
// Created by jaron on 29-5-2018.
//

#include "HighscoreFactory.h"

LevelHighscore HighscoreFactory::Load(ANativeActivity* nativeActivity, std::string& levelName) {
    std::string path = _levelNameToPath(nativeActivity, levelName);

    LevelHighscore highscore = LevelHighscore();

    std::ifstream infile;
    infile.open(path, std::ios::binary);
    if (infile.is_open()) {
        infile.read(reinterpret_cast<char*>(&highscore), sizeof(LevelHighscore));
        infile.close();
    }

    return highscore;
}

int HighscoreFactory::LoadHighScore(ANativeActivity* nativeActivity, std::string& levelName) {
    LevelHighscore highscore = Load(nativeActivity, levelName);
    int highestScore = 0;

    for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++) {
        highestScore = std::max(highestScore, highscore.scores[i]);
    }

    return highestScore;
}

int HighscoreFactory::Write(ANativeActivity* nativeActivity, int score, std::string& levelName) {
    std::string path = _levelNameToPath(nativeActivity, levelName);

    struct stat sb;
    int32_t res = stat(nativeActivity->internalDataPath, &sb);
    if (res == ENOENT) {
        res = mkdir(nativeActivity->internalDataPath, 0770);
    }

    LevelHighscore loadedScore = Load(nativeActivity, levelName);
    int placeAt = 0;
    for (int i = NUMBER_OF_HIGHSCORES; i >= 0; i--) {
        if (loadedScore.scores[i] > score) {
            break;
        }
        if (score > loadedScore.scores[i]) {
            placeAt = i;
        }
    }

    if (loadedScore.counter != 0) {
        for (int i = NUMBER_OF_HIGHSCORES - 1; i >= placeAt; i--) {
            loadedScore.scores[i + 1] = loadedScore.scores[i];
        }
    }

    loadedScore.scores[placeAt] = score;
    std::ofstream outfile;
    outfile.open(path, std::ios::ate | std::ios::binary);
    if (outfile.is_open()) {
        loadedScore.counter++;
        outfile.seekp(0, std::ios::beg);
        outfile.write(reinterpret_cast<const char*>(&loadedScore), sizeof(LevelHighscore));
        outfile.close();
    }

    placeAt++;
    return placeAt;
}

std::string
HighscoreFactory::_levelNameToPath(ANativeActivity* nativeActivity, std::string& levelName) {
    // levelName may contain dots and slashes, which is bad if we're going to add it to our save path
    // Replace then with underscores to prevent whoopsiedoodles
    std::replace(levelName.begin(), levelName.end(), '/', '_');
    std::replace(levelName.begin(), levelName.end(), '.', '_');

    std::string path(nativeActivity->internalDataPath);
    path += "/highscore-";
    path += levelName;
    path += ".bin";

    return path;
}



