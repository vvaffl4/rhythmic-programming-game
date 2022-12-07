//
// Created by patri on 4/20/2018.
//

#include "Model.h"

void Model::SetColor(const glm::vec3& color) {
    _color.x = color.x;
    _color.y = color.y;
    _color.z = color.z;
}

void Model::SetAlpha(float alpha) {
    _color.a = alpha;
}
