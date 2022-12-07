//
// Created by michelle on 08/06/18.
//

#include "TexturedButton.h"

TexturedButton::TexturedButton(Texture* texture, short x, short y, short width, short height)
        : UIButton(x, y, width, height) {

    _setTexture(texture);
}

TexturedButton::TexturedButton(AAssetManager* assetManager, std::string name, short x, short y,
                               short width, short height)
        : UIButton(x, y, width, height) {
    Texture* tex = ResourceManager::CreateTextureObjectFromAsset(assetManager, name.c_str());

    if (tex && tex != nullptr) {
        _texture = tex;
        _setTexture(tex);
    }
}

TexturedButton::~TexturedButton() {
    if (_visible) {
        _removeFromRender();
    }

    if (_texture != nullptr) {
        delete _texture;
        _texture = nullptr;
    }
}

void TexturedButton::_setTexture(Texture* texture) {
    _sprite->SetTexture(texture);
    _addToRender();
}

void TexturedButton::SetVisible(bool b) {
    if (_visible != b) {
        if (b) {
            _addToRender();
        } else {
            _removeFromRender();
        }
    }

    UIObject::SetVisible(b);
}

void TexturedButton::_addToRender() {
    ServiceManager::GetInstance().Send(new Message{
            MessageType::ADD_OBJECT2D,
            _sprite
    });
}

void TexturedButton::_removeFromRender() {
    ServiceManager::GetInstance().Send(new Message{
            MessageType::REMOVE_OBJECT2D,
            _sprite
    });
}
