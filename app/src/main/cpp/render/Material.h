//
// Created by pw on 20-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_MATERIAL_H
#define RHYTHMICPROGRAMMING_MATERIAL_H


#include "Shader.h"
#include "ShaderManager.h"

class Material {
protected:
    std::string _shader;
public:
    Material(std::string& shader);

    virtual ~Material();

    virtual void Use() = 0;

    const Shader* GetShader();
};


#endif //RHYTHMICPROGRAMMING_MATERIAL_H
