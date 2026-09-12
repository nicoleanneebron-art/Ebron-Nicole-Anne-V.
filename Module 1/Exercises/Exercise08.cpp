#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black background
    glClear(GL_COLOR_BUFFER_BIT);

    glShadeModel(GL_SMOOTH); // enable smooth color blending

    glBegin(GL_POLYGON);

    // Top vertex (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.7f);

    // Right vertex (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.7f, 0.0f);

    // Bottom vertex (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, -0.7f);

    // Left vertex (Yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(-0.7f, 0.0f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex08 - Smooth Shaded Diamond");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}