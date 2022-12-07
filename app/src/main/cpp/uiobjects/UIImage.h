//
// Created by patri on 6/6/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_UIIMAGE_H
#define RHYTHMIC_PROGRAMMING_GAME_UIIMAGE_H


#include "UIObject.h"

class UIImage : public UIObject {
public:
    UIImage(short x, short y, short width, short height);

    void ProcessInput(Input* input) override;
};

#endif //RHYTHMIC_PROGRAMMING_GAME_UIIMAGE_H
