#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint lineVBO = 0;

const GLsizeiptr POSITION_BYTES = 4 * sizeof(GLfloat);

void initBuffer() {
    GLfloat positions[] = {
        -0.7f, 0.0f, 0.7f, 0.0f
    };

    GLfloat colors[] = {
        0.25f, 0.75f, 1.0f, 0.95f, 0.35f, 0.35f
    };

    glGenBuffers(1, &lineVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);

    glBufferData(GL_ARRAY_BUFFER, POSITION_BYTES + sizeof(colors), nullptr, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, POSITION_BYTES, positions);

    glBufferSubData(GL_ARRAY_BUFFER, POSITION_BYTES, sizeof(colors), colors);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(7.0f);

    glEnableClientState(GL_VERTEX_ARRAY);

    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);

    glVertexPointer(2, GL_FLOAT, 0, (void*)0);

    glColorPointer(3, GL_FLOAT, 0, (void*)POSITION_BYTES);

    glDrawArrays(GL_LINES, 0, 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableClientState(GL_COLOR_ARRAY);

    glDisableClientState(GL_VERTEX_ARRAY);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(650, 420);

    glutCreateWindow("Q06 - glBufferSubData Colored Line");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;

#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);

    initBuffer();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
