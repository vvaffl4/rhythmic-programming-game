//
// Created by pw on 20-4-2018.
//

#ifndef RHYTHMICPROGRAMMING_MESH_H
#define RHYTHMICPROGRAMMING_MESH_H

#include <GLES3/gl31.h>

class Mesh {
private:
    GLuint _vertexArrayObject = GL_ZERO;
    GLuint _vertexBufferObject = GL_ZERO;

    bool _initialized = false;

public:
    ~Mesh();

    void LoadMesh(GLfloat* vertices, unsigned short count);

    void Use();
};


#endif //RHYTHMICPROGRAMMING_MESH_H
