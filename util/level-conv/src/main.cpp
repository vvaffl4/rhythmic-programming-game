#include <iostream>
#include <map>
#include <fstream>
#include "../lib/json.hpp"

#define LEVELFACTORY_STRUCTS_ONLY
#include "../../../app/src/main/cpp/LevelFactory.h"

using json = nlohmann::json;

const char MAGIC_NUMBER[4] = "BLF";

void save(Level &, const char*);

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Expected at least two arguments\n";
        std::cout << "Usage: level-conv [input-json] [output-bin]\n";

        return -1;
    }

    const char* INPUT_JSON = argv[1];
    const char* OUTPUT_BIN = argv[2];

    std::ifstream input;
    input.open(INPUT_JSON);
    input.seekg(0, std::ios::end);
    auto file_length = (int) input.tellg();
    if (file_length <= 0) {
        std::cout << "Could not read input file " << INPUT_JSON << "\nPlease provide a valid file\n";
        return -2;
    }

    input.seekg(0, std::ios::beg);

    auto* fileContents = (char*) malloc((size_t) file_length);
    input.read(fileContents, file_length);
    input.close();

    Level level{};
    std::vector<Beat*> beatVector;

    auto jsonLevel = json::parse(fileContents);
    std::cout << jsonLevel["songName"] << std::endl;
    for (auto it = jsonLevel["beats"].begin(); it != jsonLevel["beats"].end(); it++) {
        auto filebeat = *it;
        auto* beat = new Beat();

        beat->position = filebeat["position"];
        beat->duration = filebeat["duration"];
        std::string lanestring = filebeat["lane"];
        beat->lane = lanestring.c_str()[0];

        beatVector.push_back(beat);
    }

    std::string songName = jsonLevel["songName"];
    level.levelHeader.songName = (char*) malloc(songName.length() + 1);
    strcpy(level.levelHeader.songName, songName.c_str());
    level.levelHeader.lengthMillis = jsonLevel["lengthMillis"];
    level.levelHeader.lengthSeconds = jsonLevel["lengthSeconds"];
    level.levelHeader.lengthMinutes = jsonLevel["lengthMinutes"];
    level.levelHeader.bpm = jsonLevel["bpm"];

    level.levelHeader.numberOfBeats = (int) (beatVector.size());
    level.beatArray = (Beat*) malloc(level.levelHeader.numberOfBeats * sizeof(Beat));
    for (int i = 0; i < level.levelHeader.numberOfBeats; i++) {
        level.beatArray[i] = *beatVector[i];
    }

    save(level, OUTPUT_BIN);
    free(level.beatArray);
    free(level.levelHeader.songName);
    free(fileContents);

    return 0;
}

void save(Level &level, const char* filepath) {
    std::ofstream outfile;
    outfile.open(filepath, std::ios::ate | std::ios::binary);

    char zero = 0x0;
    for (uint32_t i = 0; i < 4; i++) {
        level.fileHeader.magic[i] = MAGIC_NUMBER[i];
    }
    level.fileHeader.headerSize = sizeof(level.levelHeader);

    level.levelHeader.version = 1;
    level.levelHeader.magicMarker = 0xA0A0B0B0;
    level.levelHeader.songNameLength = (uint16_t) (strlen(level.levelHeader.songName) + 1);
    level.levelHeader.beatArrayOffset =
            (uint32_t) (sizeof(LevelFileHeader)
                        + sizeof(LevelHeader))
            + level.levelHeader.songNameLength;

    // outfile.write((char*) &level, sizeof(Level));
    outfile.write((char*) (&level.fileHeader), sizeof(LevelFileHeader));
    outfile.write((char*) (&level.levelHeader), sizeof(LevelHeader) - sizeof(char));
    outfile.write(&zero, sizeof(char));
    outfile.write(level.levelHeader.songName, level.levelHeader.songNameLength);
    if (outfile.tellp() < level.levelHeader.beatArrayOffset) {
        while (outfile.tellp() < level.levelHeader.beatArrayOffset) {
            outfile.write(&zero, sizeof(int));
        }
    }

    outfile.seekp(level.levelHeader.beatArrayOffset, std::ios::beg);
    for (uint32_t i = 0; i < level.levelHeader.numberOfBeats; i++) {
        outfile.write((char*) &level.beatArray[i], sizeof(Beat));
    }

    outfile.close();
}