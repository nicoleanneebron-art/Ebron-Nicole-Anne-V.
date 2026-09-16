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

    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLE_STRIP);

    glVertex2f(-0.5f, -0.5f); // left-bottom
    glVertex2f(-0.5f, 0.5f); // left-top
    glVertex2f(0.5f, -0.5f); // right-bottom
    glVertex2f(0.5f, 0.5f); // right-top

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q09 - Rectangle from Triangle Strip");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}