#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const float PI = 3.14159265f;

float ballX = 0.0f;
float ballY = 0.0f;
float dx = 0.005f;
float dy = 0.005f;
float radius = 0.1f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ballX, ballY);

    for (int i = 0; i <= 60; i++) {
        float angle = 2 * PI * i / 60;
        glVertex2f(
            ballX + radius * cosf(angle),
            ballY + radius * sinf(angle)
        );
    }
    glEnd();

    glFlush();
}

void idle() {
    ballX += dx;
    ballY += dy;

    if (ballX + radius > 1.0f || ballX - radius < -1.0f)
        dx = -dx;

    if (ballY + radius > 1.0f || ballY - radius < -1.0f)
        dy = -dy;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex16 - Bouncing Ball");

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}