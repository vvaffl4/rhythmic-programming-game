//
// Created by pw on 21-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_SCENE2D_H
#define RHYTHMICPROGRAMMING_SCENE2D_H

#include "Scene.h"

class Scene2D : public Scene {
private:
    glm::mat4 _projectionMatrix;
    glm::vec3 _color;
public:
    Scene2D(float top, float right, float bottom, float left);

    void Render() override;

    void SetColor(const glm::vec3& color);

    void AddModel(Model* model) override;

};


#endif //RHYTHMICPROGRAMMING_SCENE2D_H
