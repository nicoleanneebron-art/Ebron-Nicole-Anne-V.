#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const float PI = 3.14159265f;
float handAngle = PI / 2;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Clock outline
    glColor3f(1, 1, 1);

    glBegin(GL_LINE_LOOP);
    for (int i = 0;i < 60;i++) {
        float a = 2 * PI * i / 60;
        glVertex2f(0.8f * cosf(a), 0.8f * sinf(a));
    }
    glEnd();

    // Tick marks
    for (int i = 0;i < 12;i++) {
        float a = 2 * PI * i / 12;

        glBegin(GL_LINES);
        glVertex2f(0.7f * cosf(a), 0.7f * sinf(a));
        glVertex2f(0.8f * cosf(a), 0.8f * sinf(a));
        glEnd();
    }

    // Hand
    glColor3f(1, 0, 0);

    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(
        0.6f * cosf(handAngle),
        0.6f * sinf(handAngle)
    );
    glEnd();

    glFlush();
}

void idle() {
    handAngle -= 0.002f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex18 - Rotating Clock");

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}