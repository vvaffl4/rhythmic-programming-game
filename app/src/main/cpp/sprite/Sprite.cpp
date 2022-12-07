//
// Created by pw on 21-4-2018.
//

#include "Sprite.h"

void Sprite::_init(Texture* texture, GLfloat vertices[]) {
    _texture = texture;
    _vertices = vertices;

    _mesh = new Mesh();
    _mesh->LoadMesh(vertices, 24);

    DiffuseMaterial* material = new DiffuseMaterial("main");
    material->SetDiffuseTexture(texture);
    _material = material;
}

Sprite::Sprite(Texture* texture, GLfloat vertices[]) {
    _init(texture, vertices);
}

Sprite::Sprite(Texture* texture) {
    GLfloat vertices[] = {
            // Pos      // Tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };

    _init(texture, vertices);
}

Sprite::Sprite() {}

Sprite::~Sprite() {
    delete _mesh;
    delete _material;
}

void Sprite::SetTexture(Texture* texture) {
    dynamic_cast<DiffuseMaterial*>(_material)->SetDiffuseTexture(texture);
}

void Sprite::Render(glm::mat4& matrix) {

    _material->Use();

    _material->GetShader()->SetMatrix4f("model", _modelMatrix);
    _material->GetShader()->SetMatrix4f("projection", matrix);
    _material->GetShader()->SetVec4f("color", _color);

    _mesh->Use();

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Sprite::SetZIndex(short index) {
    SetPosition(_position.x, _position.y, index);
}

Sprite::Sprite(Sprite*& pSprite) {
    _init(pSprite->_texture, pSprite->_vertices);
}

void Sprite::SetDimensions(int width, int height) {

    _width = width;
    _height = height;
}

int Sprite::GetHeight() {
    return _height;
}

int Sprite::GetWidth() {
    return _width;
}

