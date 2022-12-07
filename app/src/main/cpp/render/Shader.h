//
// Created by pw on 20-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_SHADER_H
#define RHYTHMICPROGRAMMING_SHADER_H

#include <iostream>
#include <android/log.h>
#include <string>
#include <GLES3/gl31.h>

#include "../glm/gtc/type_ptr.hpp"
#include "../glm/detail/type_mat.hpp"


class Shader {
private:
    GLuint _programId = GL_ZERO;
    GLuint _vsh = GL_ZERO;
    GLuint _fsh = GL_ZERO;

    bool _initialized = false;

    GLuint _createShader(const std::string& source, GLenum type);

    GLuint _createProgram(GLuint vertexId, GLuint fragmentId);

public:
    Shader(std::string vertexShaderSource, std::string fragmentShaderSource);

    ~Shader();

    void Use();

    void SetMatrix4f(const std::string& name, glm::mat4& matrix) const;

    void SetVec4f(const std::string& name, glm::vec4 vector) const;
};


#endif //RHYTHMICPROGRAMMING_SHADER_H
