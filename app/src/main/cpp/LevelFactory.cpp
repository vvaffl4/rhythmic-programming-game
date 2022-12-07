//
// Created by michelle on 19/04/18.
//

#include "LevelFactory.h"

Level* LevelFactory::Load(AAssetManager* assetManager, const std::string& path) {
    const char* c_path = path.c_str();

    Level* level = _cache[c_path];
    if (level != nullptr) {
        return level;
    }

    AAsset* asset = AAssetManager_open(assetManager, path.c_str(), AASSET_MODE_UNKNOWN);
    if (asset == NULL) {
        return nullptr;
    }

    level = new Level();
    AAsset_read(asset, (void*) (&(level->fileHeader)), sizeof(LevelFileHeader));
    AAsset_read(asset, (void*) (&(level->levelHeader)), sizeof(LevelHeader) - sizeof(char));
    AAsset_seek(asset, sizeof(char), SEEK_CUR);
    level->levelHeader.songName = (char*) malloc(level->levelHeader.songNameLength);
    AAsset_read(asset, (void*) level->levelHeader.songName, level->levelHeader.songNameLength);

    AAsset_seek(asset, level->levelHeader.beatArrayOffset, SEEK_SET);
    const size_t beatArrayMemSize = level->levelHeader.numberOfBeats * sizeof(Beat);
    level->beatArray = (Beat*) malloc(beatArrayMemSize);
    AAsset_read(asset, (void*) level->beatArray, beatArrayMemSize);

    AAsset_close(asset);

    _cache[c_path] = level;
    return level;
}
