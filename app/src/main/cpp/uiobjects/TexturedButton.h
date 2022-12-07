//
// Created by michelle on 08/06/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_TEXTUREDBUTTON_H
#define RHYTHMIC_PROGRAMMING_GAME_TEXTUREDBUTTON_H

#include "UIButton.h"
#include "../ResourceManager.h"

class TexturedButton : public UIButton {
private:
    Texture* _texture = nullptr;

    void _setTexture(Texture* texture);

public:
    TexturedButton(Texture* texture, short x, short y, short width, short height);

    TexturedButton(AAssetManager* assetManager, std::string name, short x, short y, short width,
                   short height);

    virtual ~TexturedButton();

    void SetVisible(bool b) override;

    void _addToRender();

    void _removeFromRender();
};


#endif //RHYTHMIC_PROGRAMMING_GAME_TEXTUREDBUTTON_H
