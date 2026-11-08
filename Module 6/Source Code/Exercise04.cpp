#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint triangleVBO = 0;

void translateX(float x, int startindex) {
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    GLfloat* mapV = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));

    if (mapV != nullptr) {
        mapV[startindex] += x;

        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void initBuffer() {
    GLfloat triangle[] = {
        0.0f, 0.65f, 0.0f, -0.6f, -0.5f, 0.0f, 0.6f, -0.5f, 0.0f
    };

    glGenBuffers(1, &triangleVBO);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    for (int i = 0; i < 9; i += 3) translateX(0.25f, i);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.30f, 0.85f, 0.65f);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(600, 500);

    glutCreateWindow("Q04 - translateX Helper");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;

#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);

    initBuffer();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
