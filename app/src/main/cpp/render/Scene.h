//
// Created by pw on 20-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_SCENE_H
#define RHYTHMICPROGRAMMING_SCENE_H

#include <algorithm>
#include <vector>
#include "Model.h"

class Scene {
protected:
    std::vector<Model*> _models;
public:
    virtual ~Scene();

    virtual void Render() = 0;

    virtual void AddModel(Model* model);

    void RemoveModel(Model* model);
};


#endif //RHYTHMICPROGRAMMING_SCENE_H
