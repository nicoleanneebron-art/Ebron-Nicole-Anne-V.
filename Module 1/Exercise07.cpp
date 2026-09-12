#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f); //red triangle (left)
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.8f, -0.5f);
    glVertex2f(-0.5f, 0.4f);
    glVertex2f(-0.2f, -0.5f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); //blue triangle (right)
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2f, -0.5f);
    glVertex2f(0.5f, 0.4f);
    glVertex2f(0.8f, -0.5f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex07 - Two Triangles");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}