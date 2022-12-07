//
// Created by michelle on 16/05/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_SPRITESHEETFONT_H
#define RHYTHMIC_PROGRAMMING_GAME_SPRITESHEETFONT_H


#include "Spritesheet.h"

class SpritesheetFont {
private:
    std::map<std::string, std::string> _lookupTable;

    Spritesheet* _spritesheet = nullptr;
public:
    SpritesheetFont();

    std::vector<Sprite*> StringToSprites(std::string s);

    void AddLetter(std::string& letter, std::string spriteName);

    SpritesheetFont(Spritesheet* pSpritesheet);
};


#endif //RHYTHMIC_PROGRAMMING_GAME_SPRITESHEETFONT_H
