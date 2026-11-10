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
void APIENTRY debugCallback(GLenum, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*) {
    std::cerr << "OpenGL debug message - type " << type
              << ", severity " << severity << ": " << message << '\n';
}
#endif

void setupProjection(int width, int height) {
    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, static_cast<double>(width) / height, 1.0, 20.0);
    glEnable(static_cast<GLenum>(0xDEAD));
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -4.0f);
    glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(35.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.3f, 0.85f, 0.7f);
    glutSolidCube(1.5);
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q17 - OpenGL Error Callback");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    if (GLEW_VERSION_4_3 || GLEW_KHR_debug) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugCallback, nullptr);
    } else {
        std::cerr << "Debug callbacks are not supported by this OpenGL context.\n";
    }
#endif
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    setupProjection(800, 600);
    glutDisplayFunc(display);
    glutReshapeFunc(setupProjection);
    glutMainLoop();
    return 0;
}
