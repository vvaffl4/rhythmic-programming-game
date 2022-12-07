//
// Created by pw on 20-4-2018.
//

#include "Material.h"

Material::Material(std::string& shader) : _shader(shader) {}

Material::~Material() {

}

const Shader* Material::GetShader() {
    return ShaderManager::GetInstance().GetShader(_shader);
}

