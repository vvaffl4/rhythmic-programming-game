//
// Created by pw on 20-4-2018.
//
#include "Transform.h"

void Transform::Translate(const glm::vec3& translation) {
    _position += translation;
    _UpdateTransformMatrix();
}

void Transform::Translate(float x, float y, float z) {
    _position += glm::vec3(x, y, z);
    _UpdateTransformMatrix();
}

void Transform::SetPosition(const glm::vec3& position) {
    _position = position;
    _UpdateTransformMatrix();
}

void Transform::SetPosition(float x, float y, float z) {
    _position = glm::vec3(x, y, z);
    _UpdateTransformMatrix();
}

void Transform::SetRotation(const glm::quat& rotation) {
    _rotation = rotation;
    _UpdateTransformMatrix();
}

void Transform::SetScale(float x, float y, float z) {
    _scale = glm::vec3(x, y, z);
    _UpdateTransformMatrix();
}

void Transform::SetScale(const glm::vec3& scale) {
    _scale = scale;
    _UpdateTransformMatrix();
}

void Transform::_UpdateTransformMatrix() {
    _modelMatrix = glm::translate(glm::mat4(1.0f), _position);
    _modelMatrix = glm::scale(_modelMatrix, _scale);
    _modelMatrix = glm::rotate(_modelMatrix, glm::angle(_rotation), glm::axis(_rotation));
}
