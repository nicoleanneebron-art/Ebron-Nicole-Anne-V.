#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.25f, 0.8f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(300.0f, 225.0f);
    glVertex2f(500.0f, 225.0f);
    glVertex2f(500.0f, 375.0f);
    glVertex2f(300.0f, 375.0f);
    glEnd();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q06 - Pixel-Style Coordinates");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
