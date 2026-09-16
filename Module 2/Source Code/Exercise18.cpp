#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

void display() {

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUAD_STRIP);

    glColor3f(1, 0, 0);
    glVertex2f(-0.9f, -0.3f);
    glVertex2f(-0.9f, 0.3f);

    glColor3f(1, 0, 0);
    glVertex2f(-0.5f, -0.3f);
    glVertex2f(-0.5f, 0.3f);

    glColor3f(0, 1, 0);
    glVertex2f(-0.1f, -0.3f);
    glVertex2f(-0.1f, 0.3f);

    glColor3f(0, 0, 1);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.3f, 0.3f);

    glColor3f(1, 1, 0);
    glVertex2f(0.7f, -0.3f);
    glVertex2f(0.7f, 0.3f);

    glColor3f(1, 0, 1);
    glVertex2f(0.9f, -0.3f);
    glVertex2f(0.9f, 0.3f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q18 - Alternating Color Ribbon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}