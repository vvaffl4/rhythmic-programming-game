//
// Created by michelle on 08/06/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_LABEL_H
#define RHYTHMIC_PROGRAMMING_GAME_LABEL_H

#include "UIObject.h"
#include "../sprite/SpriteString.h"
#include "../sprite/StringRenderData.cpp"

class Label : public UIObject {
private:
    static int __counter;

    AAssetManager* _assetManager;
    StringAlignment _alignment = StringAlignment::ALIGN_LEFT;
    std::string _renderKey;
    std::string _font;
    std::string _text;
    float _scale = 1.0f;
    float _calculatedHeight = -.00001f;
    StringRenderData* _stringRenderData = nullptr;
    bool _rendered = false;

    void _updateRenderData();

    void _updateHeight();

public:
    ~Label();

    Label(AAssetManager* assetManager, short x, short y, short width, short height);

    Label(AAssetManager* assetManager, short x, short y) : Label::Label(assetManager, x, y, 0,
                                                                        0) {};

    void SetText(const char* text) {
        std::string str = text;
        this->SetText(str);
    };

    void SetScale(float scale);

    void SetText(std::string& text);

    void Render();

    void ProcessInput(Input* input) override {};

    void SetX(short x) override;

    void SetY(short y) override;

    float GetCalculatedHeight() { return _calculatedHeight; };
};


#endif //RHYTHMIC_PROGRAMMING_GAME_LABEL_H
