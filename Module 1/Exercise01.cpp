#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);   // red point
    glPointSize(15.0f);            // make the point big enough to see

    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);    // the origin, dead center of the window
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex01 - Red Center Point");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
