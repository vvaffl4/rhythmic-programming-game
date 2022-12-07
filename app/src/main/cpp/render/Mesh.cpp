//
// Created by pw on 20-4-2018.
//

#include "Mesh.h"

Mesh::~Mesh() {
    if (_initialized) {
        glDeleteVertexArrays(1, &_vertexArrayObject);
        glDeleteBuffers(1, &_vertexBufferObject);
        _initialized = false;
    }
}

void Mesh::LoadMesh(GLfloat* vertices, unsigned short count) {

    glGenVertexArrays(1, &_vertexArrayObject);
    glGenBuffers(1, &_vertexBufferObject);

    // Set Data in Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    // Enable vertex array of shader
    glBindVertexArray(_vertexArrayObject);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) 0);

    // Unbind Vertex Array and Buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _initialized = true;
}

void Mesh::Use() {
    if (_initialized) glBindVertexArray(_vertexArrayObject);
}
