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

    glColor3f(1.0f, 1.0f, 1.0f); // white lines
    glLineWidth(3.0f);

    glBegin(GL_LINES);

    // Horizontal line
    glVertex2f(-0.8f, 0.3f);
    glVertex2f(-0.2f, 0.3f);

    // Vertical line
    glVertex2f(0.4f, -0.6f);
    glVertex2f(0.4f, 0.0f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q02 - Two Unconnected Lines");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}