//
// Created by patri on 6/6/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_PARTICLEPROPERTIES_H
#define RHYTHMIC_PROGRAMMING_GAME_PARTICLEPROPERTIES_H

#include "../glm/glm.hpp"
#include "../glm/gtx/simd_quat.hpp"

struct ParticleProperties {
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
    float alpha;
};

#endif //RHYTHMIC_PROGRAMMING_GAME_PARTICLEPROPERTIES_H
