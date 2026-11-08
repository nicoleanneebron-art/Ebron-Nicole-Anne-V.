#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint topFaceVBO = 0;

void initBuffer() {
    GLfloat topFace[] = {
        -0.8f, 0.6f, -0.8f,  0.8f, 0.6f, -0.8f,
        0.8f, 0.6f,  0.8f, -0.8f, 0.6f,  0.8f
    };

    glGenBuffers(1, &topFaceVBO);

    glBindBuffer(GL_ARRAY_BUFFER, topFaceVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(topFace), topFace, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -4.0f);

    glRotatef(28.0f, 1.0f, 0.0f, 0.0f);

    glRotatef(-28.0f, 0.0f, 1.0f, 0.0f);

    glColor3f(0.25f, 0.75f, 0.90f);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, topFaceVBO);

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glDrawArrays(GL_QUADS, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(55.0, static_cast<double>(w) / h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(650, 520);

    glutCreateWindow("Q02 - VBO Cube Top Face");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;

#endif
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);

    initBuffer();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
