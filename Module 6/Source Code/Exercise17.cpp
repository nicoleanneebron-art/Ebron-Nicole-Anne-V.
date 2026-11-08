#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>

#ifndef __APPLE__
void APIENTRY debugCallback(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar* message, const void*) {
    std::cerr<<"OpenGL debug: "<<message<<std::endl;
}

#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q17 - OpenGL Debug Callback");

#ifndef __APPLE__
    if (glewInit()!=GLEW_OK)return 1;

    if (GLEW_KHR_debug||GLEW_VERSION_4_3) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugCallback, nullptr);

        glEnable(static_cast<GLenum>(0xFFFFFFFFu));

        glFinish();
    }
    else{
        std::cerr<<"KHR_debug is unavailable on this context."<<std::endl;
    }

#endif
    glClearColor(.06f, .09f, .14f, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
