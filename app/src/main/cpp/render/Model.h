//
// Created by patri on 4/20/2018.
//

#ifndef RHYTHMICPROGRAMMING_MODEL_H
#define RHYTHMICPROGRAMMING_MODEL_H

#include "GLES/gl.h"
#include "../glm/vec3.hpp"
#include "../glm/vec2.hpp"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"

#include <android/log.h>

class Model : public Transform {
protected:
    Material* _material = nullptr;
    Mesh* _mesh = nullptr;

    glm::vec4 _color = glm::vec4(1.0f);
public:
    virtual void Render(glm::mat4& matrix) = 0;

    void SetColor(const glm::vec3& color);

    void SetAlpha(float alpha);
};


#endif //RHYTHMICPROGRAMMING_MODEL_H
