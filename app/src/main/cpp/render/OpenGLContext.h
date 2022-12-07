//
// Created by patri on 4/18/2018.
//

#ifndef RHYTHMICPROGRAMMING_GRAPHICSRENDERER_H
#define RHYTHMICPROGRAMMING_GRAPHICSRENDERER_H

#include <android/log.h>
#include <initializer_list>

// For egl
#include <EGL/egl.h>
#include <EGL/eglplatform.h>

// For OpenGL
#include <GLES3/gl31.h>

class OpenGLContext {
private:
    EGLDisplay _display;
    EGLContext _context;
    EGLSurface _surface;
    EGLint _width;
    EGLint _height;

public:
    OpenGLContext() {};

    ~OpenGLContext() { this->DestroyOpenGLContext(); };

    void CreateOpenGLContext(ANativeWindow* window);

    void DestroyOpenGLContext();

    void SwapBuffers();
};


#endif //RHYTHMICPROGRAMMING_GRAPHICSRENDERER_H
