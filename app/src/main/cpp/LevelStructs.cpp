//
// Created by michelle on 26/04/18.
//


#ifndef LEVELSTRUCTS_CPP
#define LEVELSTRUCTS_CPP

#include <cstdint>

struct LevelFileHeader {
    char magic[4];
    uint32_t headerSize;
};

struct LevelHeader {
    uint16_t version;
    float lengthMillis;
    float lengthSeconds;
    float lengthMinutes;
    uint32_t bpm;
    uint32_t numberOfBeats;
    uint32_t magicMarker;
    uint32_t beatArrayOffset;
    uint16_t songNameLength;
    char* songName;
};

struct Beat {
    float position;
    float duration;
    char lane;
};

struct Level {
    LevelFileHeader fileHeader;
    LevelHeader levelHeader;

    Beat* beatArray;
};

#endif // LEVELSTRUCTS_CPP