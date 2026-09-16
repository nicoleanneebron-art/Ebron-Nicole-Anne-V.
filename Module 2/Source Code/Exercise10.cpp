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

void display() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.5f, 0.0f); // orange

    glBegin(GL_TRIANGLE_FAN);

    // center
    glVertex2f(0.0f, 0.0f);

    for (int i = 0;i <= 8;i++) {
        float angle = PI * i / 8.0f;

        glVertex2f(
            0.7f * cosf(angle),
            0.7f * sinf(angle)
        );
    }

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q10 - Half Circle Fan");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}