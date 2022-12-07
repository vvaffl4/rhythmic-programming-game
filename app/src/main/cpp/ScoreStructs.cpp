//
// Created by jaron on 29-5-2018.
//

#ifndef SCORESTRUCTS_CPP
#define SCORESTRUCTS_CPP

#define NUMBER_OF_HIGHSCORES 10

struct LevelHighscore {
    // Improve recognisability of the file outside of the game.
    const char MAGIC[4] = "RHY";
    short version = 1;
    int scores[NUMBER_OF_HIGHSCORES];
    long counter = 0;
};


#endif
