//
// Created by michelle on 09/05/18.
//

#include "Spritesheet.h"

void Spritesheet::AddSprite(std::string name, int x, int y, int w, int h) {
    SpriteDefinition sprite(name, x, y, w, h);
    _sprites.push_back(sprite);
}

Spritesheet::Spritesheet(AAssetManager* assetManager, std::string spritesheetPath) {
    _assetManager = assetManager;
    _spritesheetPath = spritesheetPath;

    _loadTexture();
}

Spritesheet::~Spritesheet() {
    for (auto it = _spriteCache.begin(); it != _spriteCache.end(); it++) {
        delete (it->second);
    }
    _spriteCache.clear();
}

void Spritesheet::_loadTexture() {

    _texture = ResourceManager::CreateTextureObjectFromAsset(_assetManager,
                                                             _spritesheetPath.c_str());
    _textureWidth = _texture->GetWidth();
    _textureHeight = _texture->GetHeight();
}

Sprite* Spritesheet::Get(std::string name) {
    return Get(name, false);
}

Sprite* Spritesheet::Get(std::string name, bool skipCache) {
    if (_spriteCache[name] && !skipCache) {
        return _spriteCache[name];
    }

    for (auto it = _sprites.begin(); it != _sprites.end(); it++) {
        if (it->GetName() == name) {
            Sprite* sprite = it->CreateSprite(_texture, _textureWidth,
                                              _textureHeight);
            if (!skipCache) _spriteCache[name] = sprite;
            return sprite;
        }
    }

    return nullptr;
}
