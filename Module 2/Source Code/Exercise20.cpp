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
const int SEGMENT_COUNT = 60;

void display() {

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(1, 1, 1);
    glVertex2f(0.0f, 0.0f);

    for (int i = 0; i <= SEGMENT_COUNT; i++) {

        float t = (float)i / SEGMENT_COUNT;
        float angle = t * 2.0f * PI;

        float r = 0.5f + 0.5f * sinf(angle);
        float g = 0.5f + 0.5f * sinf(angle + 2.0f * PI / 3.0f);
        float b = 0.5f + 0.5f * sinf(angle + 4.0f * PI / 3.0f);

        glColor3f(r, g, b);

        glVertex2f(
            0.8f * cosf(angle),
            0.8f * sinf(angle)
        );
    }

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Q20 - Procedural Rainbow Fan");

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}