#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const float PI = 3.14159265f;

void drawCircleOutline(float radius, float r, float g, float b) {
    glColor3f(r, g, b);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 60; i++) {
        float angle = 2.0f * PI * i / 60;
        glVertex2f(radius * cosf(angle), radius * sinf(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawCircleOutline(0.2f, 1.0f, 0.0f, 0.0f);
    drawCircleOutline(0.4f, 0.0f, 1.0f, 0.0f);
    drawCircleOutline(0.6f, 0.0f, 0.0f, 1.0f);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex11 - Concentric Circles");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}