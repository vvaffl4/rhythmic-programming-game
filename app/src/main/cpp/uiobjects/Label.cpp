//
// Created by michelle on 08/06/18.
//

#include "Label.h"

int Label::__counter = 0;

Label::Label(AAssetManager* assetManager, short x, short y, short width, short height) :
        UIObject(x, y, width, height) {

    _assetManager = assetManager;
    _text = "";
    _font = "abc-font.ini";

    _renderKey = "Label-";
    _renderKey += Label::__counter;
    Label::__counter++;

    _updateRenderData();
}

Label::~Label() {
    UIObject::~UIObject();

    if (_stringRenderData != nullptr) {
        ServiceManager::GetInstance().Send(new Message{
                MessageType::UNRENDER_STRING,
                &_renderKey
        });

        delete _stringRenderData;
        _stringRenderData = nullptr;
    }

    Label::__counter--;
}

void Label::SetText(std::string& text) {
    _text = text;
    _updateRenderData();
    Render();
}

void Label::_updateRenderData() {
    if (_stringRenderData != nullptr) {
        delete _stringRenderData;
    }

    if (_calculatedHeight <= 0.0f) {
        _updateHeight();
    }

    _stringRenderData = new StringRenderData{
            _renderKey.c_str(),
            _font.c_str(),
            _text.c_str(),
            _scale,
            _x,
            _y,
            _alignment,
            0.0f
    };

    if (_rendered) {
        Render();
    }
}

void Label::Render() {
    ServiceManager::GetInstance().Send(new Message{
            MessageType::RENDER_STRING,
            _stringRenderData
    });

    _rendered = true;
}

void Label::SetX(short x) {
    _x = x;
    _updateRenderData();
}

void Label::SetY(short y) {
    _y = y;
    _updateRenderData();
}

void Label::SetScale(float scale) {
    _scale = scale;
    _updateHeight();
    _updateRenderData();
}

void Label::_updateHeight() {
    SpriteString spriteString(_assetManager, _font, _text);
    spriteString.SetPosition(0, 0, _alignment, _scale);
    _calculatedHeight = spriteString.GetHeight();
}
