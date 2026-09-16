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

    glColor3f(0.0f, 1.0f, 1.0f); // cyan
    glLineWidth(3.0f);

    glBegin(GL_LINE_STRIP);

    glVertex2f(-0.8f, 0.5f);
    glVertex2f(-0.4f, -0.2f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.4f, -0.2f);
    glVertex2f(0.8f, 0.5f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q03 - Zig-Zag Line Strip");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}