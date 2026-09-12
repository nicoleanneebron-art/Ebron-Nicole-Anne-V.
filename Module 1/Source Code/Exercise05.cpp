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
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);  // light gray
    glColor3f(0.0f, 0.0f, 0.0f);  // black
    glLineWidth(3.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.5f, 0.5f);   // top right
    glVertex2f(0.5f, -0.5f);  // bottom right
    glVertex2f(-0.5f, -0.5f); // bottom left
    glVertex2f(-0.5f, 0.5f);  // top left
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex05 - Square Outline on Gray Background");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
