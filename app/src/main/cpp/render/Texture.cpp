//
// Created by patrick on 4/20/2018.
//
#include "Texture.h"

Texture::Texture(GLuint id, unsigned int width, unsigned int height) :
        _id(id),
        _width(width),
        _height(height) {
    if (_id != GL_ZERO) {
        _initialized = true;
    }
}

Texture::~Texture() {
    if (_initialized) {
        glDeleteTextures(1, &_id);
    }
}

void Texture::Use() {
    if (_initialized) glBindTexture(GL_TEXTURE_2D, _id);
}

unsigned int Texture::GetWidth() {
    return _width;
}

unsigned int Texture::GetHeight() {
    return _height;
}
