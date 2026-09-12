#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const float PI = 3.14159265f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Ground
    glColor3f(0.0f, 0.7f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.3f);
    glVertex2f(-1.0f, -0.3f);
    glEnd();

    // Sun
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.7f, 0.7f);

    for (int i = 0;i <= 60;i++) {
        float angle = 2 * PI * i / 60;
        glVertex2f(
            0.7f + 0.15f * cosf(angle),
            0.7f + 0.15f * sinf(angle)
        );
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(800, 400);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Ex14 - Simple Landscape");

    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}