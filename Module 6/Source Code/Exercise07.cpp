#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint triangleVBO = 0;

void initBuffer() {
    GLfloat vertices[] = {
        0.0f, 0.7f, -0.7f, -0.55f, 0.7f, -0.55f
    };

    glGenBuffers(1, &triangleVBO);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.30f, 0.82f, 0.72f);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glVertexPointer(2, GL_FLOAT, 0, (void*)0);

    glBegin(GL_TRIANGLES);

    glArrayElement(0);

    glArrayElement(1);

    glArrayElement(2);

    glEnd();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(600, 500);

    glutCreateWindow("Q07 - glArrayElement Basics");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;

#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);

    initBuffer();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
