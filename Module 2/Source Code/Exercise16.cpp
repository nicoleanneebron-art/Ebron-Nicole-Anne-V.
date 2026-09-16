#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
using namespace std;

const float PI = 3.14159265f;

void drawCircle() {

    glColor3f(1.0f, 0.4f, 0.7f);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(0.0f, 0.3f);

    for (int i = 0; i <= 40; i++) {
        float angle = 2 * PI * i / 40;

        glVertex2f(
            0.25f * cosf(angle),
            0.3f + 0.25f * sinf(angle)
        );
    }

    glEnd();
}

void drawBase() {

    glColor3f(0.7f, 0.4f, 0.1f);

    glBegin(GL_QUADS);

    glVertex2f(-0.15f, -0.6f);
    glVertex2f(0.15f, -0.6f);
    glVertex2f(0.15f, 0.1f);
    glVertex2f(-0.15f, 0.1f);

    glEnd();
}

void display() {

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    drawCircle();
    drawBase();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q16 - Fan and Quad Composition");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}