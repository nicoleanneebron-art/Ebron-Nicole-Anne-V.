#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint quadVBO = 0;

void scaleAll(float* vertex, float sx, float sy, float sz) {
    float matrix[16] = {
        sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1
    };

    float x = vertex[0], y = vertex[1], z = vertex[2], w = 1.0f;

    vertex[0] = matrix[0] * x + matrix[4] * y + matrix[8] * z + matrix[12] * w;

    vertex[1] = matrix[1] * x + matrix[5] * y + matrix[9] * z + matrix[13] * w;

    vertex[2] = matrix[2] * x + matrix[6] * y + matrix[10] * z + matrix[14] * w;
}

void initBuffer() {
    GLfloat quad[] = {
        -0.3f, -0.25f, 0, 0.3f, -0.25f, 0, 0.3f, 0.25f, 0, -0.3f, 0.25f, 0
    };

    for (int i = 0; i < 12; i += 3) scaleAll(&quad[i], 2.0f, 2.0f, 1.0f);

    glGenBuffers(1, &quadVBO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.25f, 0.75f, 0.90f);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glDrawArrays(GL_QUADS, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);

    glutCreateWindow("Q08 - Scale Every Vertex");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;

#endif
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
