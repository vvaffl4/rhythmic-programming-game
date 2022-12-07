//
// Created by michelle on 16/05/18.
//

#include "SpritesheetFont.h"

SpritesheetFont::SpritesheetFont() {

}

void SpritesheetFont::AddLetter(std::string& letter, std::string spriteName) {
    _lookupTable[letter] = spriteName;
}

std::vector<Sprite*> SpritesheetFont::StringToSprites(std::string s) {
    std::vector<Sprite*> spriteList;
    for (int i = 0; i < s.size(); i++) {
        std::string c(1, s[i]);

        Sprite* sprite = _spritesheet->Get(_lookupTable[c], true);
        spriteList.push_back(sprite);
    }

    return spriteList;
}

SpritesheetFont::SpritesheetFont(Spritesheet* pSpritesheet) {
    _spritesheet = pSpritesheet;
}
