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

    glColor3f(0.2f, 0.7f, 1.0f); // light blue

    glBegin(GL_QUADS);

    glVertex2f(-0.6f, 0.5f);
    glVertex2f(0.5f, 0.6f);
    glVertex2f(0.7f, -0.4f);
    glVertex2f(-0.5f, -0.6f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q07 - One Quadrilateral");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}