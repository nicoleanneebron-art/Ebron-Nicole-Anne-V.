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

    glColor3f(0.0f, 1.0f, 1.0f);

    glBegin(GL_QUAD_STRIP);

    glVertex2f(-0.8f, -0.6f);
    glVertex2f(-0.8f, -0.2f);

    glVertex2f(-0.3f, -0.6f);
    glVertex2f(-0.3f, 0.0f);

    glVertex2f(0.2f, -0.6f);
    glVertex2f(0.2f, 0.3f);

    glVertex2f(0.7f, -0.6f);
    glVertex2f(0.7f, 0.6f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q12 - Staircase Ribbon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}