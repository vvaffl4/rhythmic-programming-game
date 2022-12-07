//
// Created by pw on 22-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_DIFFUSEMATERIAL_H
#define RHYTHMICPROGRAMMING_DIFFUSEMATERIAL_H

#include "Material.h"
#include "Texture.h"

class DiffuseMaterial : public Material {
protected:
    Texture* _texture = nullptr;
public:
    DiffuseMaterial(std::string shader);

    ~DiffuseMaterial();

    void Use() override;

    void SetDiffuseTexture(Texture* texture);
};


#endif //RHYTHMICPROGRAMMING_DIFFUSEMATERIAL_H
