#include <iostream>
#include <fstream>
#include <cstring>

#define LEVELFACTORY_STRUCTS_ONLY
#include "../../../app/src/main/cpp/LevelFactory.h"

// Forward declerations
void save(Level&);
void load(Level&);

// SETTINGS
const char MAGIC_NUMBER[4] = "BLF";

int main(int argc, char** argv) {
	if (argc < 4) {
		std::cout << "Please provide all arguments \n";
		std::cout << "Usage: level-gen [song-name] [song-length] [bpm]\n";
		return -1;
	}
	
	// Read program arguments
	const char* SONG_NAME = argv[1];
	const char* STR_SONGLENGTH = argv[2];
	const char* STR_BPM = argv[3];
	
	if (strlen(SONG_NAME) >= 255) {
		std::cout << "Please provide a song name thats shorter than 255 characters";
		return -2;
	}
	
	// Interpreted numbers
	const float SONG_LENGTH_MS = (float) std::stoi(STR_SONGLENGTH, nullptr);
	const float BPM = (float) std::stoi(STR_BPM, nullptr);
	
	// Calculated constants
	const float SONG_LENGTH_MIN = (SONG_LENGTH_MS / 1000 / 60);
	const uint32_t n_beats = SONG_LENGTH_MIN * BPM;
	const float BEAT_LENGTH = SONG_LENGTH_MS / n_beats;
	
	// Properly construct a level structure
	Level level;
	
	// Set magic number
	for (uint32_t i = 0; i < 4; i++) {
		level.fileHeader.magic[i] = MAGIC_NUMBER[i];
	}
	
	level.fileHeader.headerSize = (uint32_t) sizeof(LevelHeader);
	
	// Populate level header with data
	level.levelHeader.version = 1;
	level.levelHeader.songName = (char*) malloc(level.levelHeader.songNameLength);
	level.levelHeader.magicMarker = 0xA0A0B0B0;
	strcpy(level.levelHeader.songName, SONG_NAME);
	
	// Populate beatmap header with data
	level.levelHeader.length = 0;
	level.levelHeader.numberOfBeats = (uint32_t) n_beats;
	std::cout << "Number of beats: " << n_beats << std::endl;
	
	float beatPosition = 0;
	Beat* beats = (Beat*) malloc(n_beats * sizeof(Beat));
	for (uint32_t i = 0; i < n_beats; i++) {
		new (&(beats[i])) Beat();
		Beat* beat = &beats[i];
		beat->position = beatPosition;
		beat->duration = 1;
		beat->lane = 0x0;
		
		beatPosition += BEAT_LENGTH;
	}
	
	level.beatArray = beats;
	
	// Save the level
	save(level);
	
	// Read back for confirmation (and debugging)
	Level level2;
	// Make sure these numbers are nonsense before loading
	// helps with debuging
	level2.levelHeader.songNameLength = 1;
	level2.levelHeader.songName = (char*) (&level);
	load(level2);
	
	// for (int i = 0; i < level.levelHeader.numberOfBeats; i++) {
	// 	Beat beat = level.beatArray[i];
	// 	std::cout
	// 		<< "Read beat at "
	// 		<< beat.position
	// 		<< " in lane "
	// 		<< (int) beat.lane
	// 		<< " with duration "
	// 		<< beat.duration
	// 		<< std::endl;
	// }
	
	return 0;
}

void save(Level &level) {
	std::ofstream outfile;
	outfile.open("level.bin", std::ios::ate | std::ios::binary);
	
	level.levelHeader.songNameLength = strlen(level.levelHeader.songName) + 1;
	level.levelHeader.beatArrayOffset =
		(uint32_t) (sizeof(LevelFileHeader)
		+ sizeof(LevelHeader))
		+ level.levelHeader.songNameLength;
	std::cout
		<< "Beat array offset: "
		<< level.levelHeader.beatArrayOffset
		<< std::endl;
	
	// outfile.write((char*) &level, sizeof(Level));
	outfile.write((char*) (&level.fileHeader), sizeof(LevelFileHeader));
	outfile.write((char*) (&level.levelHeader), sizeof(LevelHeader) - sizeof(char));
	outfile.seekp(sizeof(char), std::ios::cur);
	outfile.write(level.levelHeader.songName, level.levelHeader.songNameLength);
	
	outfile.seekp(level.levelHeader.beatArrayOffset, std::ios::beg);
	for (uint32_t i = 0; i < level.levelHeader.numberOfBeats; i++) {
		outfile.write((char*) &level.beatArray[i], sizeof(Beat));
	}
	
	outfile.close();
}

void load(Level &level) {
	std::ifstream infile;
	infile.open("level.bin", std::ios::binary);
	infile.read((char*) (&level.fileHeader), sizeof(LevelFileHeader));
	infile.read((char*) (&level.levelHeader), sizeof(LevelHeader) - sizeof(char));
	infile.seekg(sizeof(char), std::ios::cur);
	level.levelHeader.songName = (char*) malloc(level.levelHeader.songNameLength);
	infile.read(level.levelHeader.songName, level.levelHeader.songNameLength);
	
	infile.seekg(level.levelHeader.beatArrayOffset, std::ios::beg);
	const int beatArrayMemSize = level.levelHeader.numberOfBeats * sizeof(Beat);
	level.beatArray = (Beat*) malloc(beatArrayMemSize);
	infile.read((char*) level.beatArray, beatArrayMemSize);
	
	infile.close();
}