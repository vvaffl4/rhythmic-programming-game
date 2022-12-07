//
// Created by pw on 22-4-2018.
//

#include "DiffuseMaterial.h"

DiffuseMaterial::DiffuseMaterial(std::string shader) : Material(shader) {

}

DiffuseMaterial::~DiffuseMaterial() {

}

void DiffuseMaterial::Use() {
    ShaderManager::GetInstance().UseShader(_shader);

    glActiveTexture(GL_TEXTURE0);

    _texture->Use();
}

void DiffuseMaterial::SetDiffuseTexture(Texture* texture) {
    _texture = texture;
}

