//
// Created by pw on 20-4-2018.
//

#include "Scene.h"

void Scene::AddModel(Model* model) {
    _models.push_back(model);
}

Scene::~Scene() {
    _models.clear();
}

void Scene::RemoveModel(Model* model) {
    _models.erase(std::remove(_models.begin(), _models.end(), model), _models.end());
}

