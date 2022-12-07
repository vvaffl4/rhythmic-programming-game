//
// Created by pw on 21-4-2018.
//

#include "Scene2D.h"
#include "../glm/gtc/matrix_transform.hpp"

Scene2D::Scene2D(float top, float right, float bottom, float left) :
        _projectionMatrix(glm::ortho(
                top,
                right,
                bottom,
                left)),
        _color(glm::vec3(1.0f)) {}

void Scene2D::Render() {
    for (auto modelIt = _models.begin(); modelIt != _models.end(); ++modelIt) {
        (*modelIt)->Render(_projectionMatrix);
    }
}

void Scene2D::AddModel(Model* model) {
    Scene::AddModel(model);
    model->SetColor(_color);
}

void Scene2D::SetColor(const glm::vec3& color) {
    _color = color;

    for (auto modelIt = _models.begin(); modelIt != _models.end(); ++modelIt) {
        (*modelIt)->SetColor(_color);
    }
}