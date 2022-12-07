//
// Created by patri on 4/20/2018.
//

#ifndef RHYTHMICPROGRAMMING_TEXTURE_H
#define RHYTHMICPROGRAMMING_TEXTURE_H

#include <string>
#include <iostream>
#include <GLES3/gl31.h>

class Texture {
private:
    GLuint _id = GL_ZERO;

    unsigned int _width;
    unsigned int _height;

    bool _initialized = false;

public:
    Texture(GLuint id, unsigned int width, unsigned int height);

    ~Texture();

    void Use();

    unsigned int GetWidth();

    unsigned int GetHeight();
};


#endif //RHYTHMICPROGRAMMING_TEXTURE_H
