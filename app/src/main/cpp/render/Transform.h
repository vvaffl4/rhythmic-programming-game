//
// Created by pw on 20-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_TRANSFORM_H
#define RHYTHMICPROGRAMMING_TRANSFORM_H

#include "../glm/glm.hpp"
#include "../glm/gtx/quaternion.hpp"
#include "../glm/gtx/transform.hpp"

class Transform {
protected:
    glm::vec3 _position;
    glm::quat _rotation;
    glm::vec3 _scale;

    glm::mat4 _modelMatrix;

    void _UpdateTransformMatrix();

public:
    void Translate(const glm::vec3& translation);

    void SetPosition(const glm::vec3& position);

    void SetPosition(float x, float y, float z);

    void SetRotation(const glm::quat& rotation);

    void SetScale(const glm::vec3& scale);

    void Translate(float x, float y, float z);

    void SetScale(float x, float y, float z);
};


#endif //RHYTHMICPROGRAMMING_TRANSFORM_H
