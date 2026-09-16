#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

void display() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glShadeModel(GL_SMOOTH);

    glBegin(GL_QUADS);

    // Top Left - Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, 0.5f);

    // Top Right - Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);

    // Bottom Right - Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.5f, -0.5f);

    // Bottom Left - Yellow
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q15 - Smoothly Shaded Square");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}