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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Red Quad
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);

    glBegin(GL_QUADS);

    glVertex2f(-0.7f, 0.5f);
    glVertex2f(0.1f, 0.5f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(-0.7f, -0.5f);

    glEnd();

    // Blue Quad
    glColor4f(0.0f, 0.0f, 1.0f, 0.5f);

    glBegin(GL_QUADS);

    glVertex2f(-0.1f, 0.5f);
    glVertex2f(0.7f, 0.5f);
    glVertex2f(0.7f, -0.5f);
    glVertex2f(-0.1f, -0.5f);

    glEnd();

    glDisable(GL_BLEND);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize(600, 600);
    glutCreateWindow("Q19 - Alpha Blended Quads");

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}