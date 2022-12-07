//
// Created by pw on 20-4-2018.
//

#define SHADER_LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Shader", __VA_ARGS__))

#include "Shader.h"

Shader::Shader(std::string vertexShaderSource, std::string fragmentShaderSource) {
    _vsh = _createShader(vertexShaderSource, GL_VERTEX_SHADER);
    _fsh = _createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    _programId = _createProgram(_vsh, _fsh);
    _initialized = true;
}

Shader::~Shader() {
    if (_initialized) {
        glUseProgram(0);
        glDeleteProgram(_programId);
        _initialized = false;
    }
}

GLuint Shader::_createShader(const std::string& source, GLenum type) {

    int success = GL_FALSE;
    char infoLog[512];

    const char* cSource = source.c_str();

    GLuint index = glCreateShader(type);
    if (!index) {
        GLint err = glGetError();
        if (err != GL_NO_ERROR) {
            SHADER_LOGI("GL error after %s(): 0x%08x\n", "VertexShader", err);
        }
    }

    glShaderSource(index, 1, &cSource, nullptr);
    glCompileShader(index);
    glGetShaderiv(index, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(index, 512, nullptr, infoLog);

        if (type == GL_VERTEX_SHADER) {
            SHADER_LOGI("Failed to compile vertex shader %s", infoLog);
        } else {
            SHADER_LOGI("Failed to compile fragment shader %s", infoLog);
        }
    }

    return index;
}

GLuint Shader::_createProgram(GLuint vertexId, GLuint fragmentId) {

    int success = GL_FALSE;
    char infoLog[512];

    const GLuint programId = glCreateProgram();
    if (!programId) {
        GLint err = glGetError();
        if (err != GL_NO_ERROR) {
            SHADER_LOGI("GL error after %s(): 0x%08x\n", "Program", err);
        }
    }

    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programId, 512, nullptr, infoLog);

        SHADER_LOGI("Failed to link shader program %s", infoLog);
    }

    glDetachShader(_programId, _vsh);
    glDetachShader(_programId, _fsh);
    glDeleteShader(_vsh);
    glDeleteShader(_fsh);

    return programId;
}

void Shader::Use() {
    if (_initialized) glUseProgram(_programId);
}

void Shader::SetMatrix4f(const std::string& name, glm::mat4& matrix) const {
    if (_initialized)
        glUniformMatrix4fv(glGetUniformLocation(_programId, &name[0]), 1, GL_FALSE,
                           glm::value_ptr(matrix));
}

void Shader::SetVec4f(const std::string& name, glm::vec4 vector) const {
    if (_initialized)
        glUniform4fv(glGetUniformLocation(_programId, &name[0]), 1, glm::value_ptr(vector));
}
