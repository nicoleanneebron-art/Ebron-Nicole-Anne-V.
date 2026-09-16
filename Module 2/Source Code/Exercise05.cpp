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

    glColor3f(1.0f, 1.0f, 1.0f); // white line
    glLineWidth(3.0f);

    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);

    glBegin(GL_LINES);
    glVertex2f(-0.8f, 0.0f);
    glVertex2f(0.8f, 0.0f);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q05 - Dashed Line");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}