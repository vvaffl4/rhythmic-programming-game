//
// Created by pw on 21-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_SPRITE_H
#define RHYTHMICPROGRAMMING_SPRITE_H

#include "../render/Model.h"
#include "../render/DiffuseMaterial.h"
#include "../InstanceTracker.h"

class Sprite : public Model {
protected:
    void _init(Texture* texture, GLfloat* vertices);

    Texture* _texture = nullptr;
    GLfloat* _vertices = nullptr;

    int _width;
    int _height;
public:

    Sprite(Sprite*& pSprite);

    Sprite(Texture* texture, GLfloat vertices[]);

    Sprite(Texture* texture);

    Sprite();

    ~Sprite();

    void Render(glm::mat4& matrix) override;

    void SetTexture(Texture* texture);

    void SetDimensions(int width, int height);

    int GetHeight();

    int GetWidth();

    void SetZIndex(short index);
};


#endif //RHYTHMICPROGRAMMING_SPRITE_H
