#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // black background
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(10.0f);

    glBegin(GL_POINTS);

    // Center - Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);

    // Up - Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);

    // Down - Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, -0.5f);

    // Left - Yellow
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, 0.0f);

    // Right - Magenta
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(0.5f, 0.0f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q01 - Plus-Shaped Colored Points");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}