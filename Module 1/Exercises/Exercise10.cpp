#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
using namespace std;

const float PI = 3.14159265f;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f); // white outline
    glLineWidth(2.0f);

    float outerRadius = 0.7f;
    float innerRadius = 0.3f;

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 10; i++) {
        float angle = PI / 2.0f + i * PI / 5.0f;

        float radius;
        if (i % 2 == 0)
            radius = outerRadius; // outer point
        else
            radius = innerRadius; // inner point

        float x = radius * cosf(angle);
        float y = radius * sinf(angle);

        glVertex2f(x, y);
    }

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex10 - Five-Pointed Star Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}