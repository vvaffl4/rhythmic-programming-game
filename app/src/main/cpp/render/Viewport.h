//
// Created by patri on 4/20/2018.
//

#ifndef RHYTHMICPROGRAMMING_VIEWPORT_H
#define RHYTHMICPROGRAMMING_VIEWPORT_H

#include <GLES3/gl31.h>

class Viewport {
private:
    short _x;
    short _y;
    short _width;
    short _height;

public:
    Viewport(short x, short y, short width, short height);

    void use();
};


#endif //RHYTHMICPROGRAMMING_VIEWPORT_H
