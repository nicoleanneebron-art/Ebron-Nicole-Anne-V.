#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const float PI = 3.14159265f;
int state = 0;

void drawCircle(float cx, float cy, float radius,
    float r, float g, float b) {

    glColor3f(r, g, b);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);

    for (int i = 0; i <= 40; i++) {
        float angle = 2 * PI * i / 40;
        glVertex2f(
            cx + radius * cosf(angle),
            cy + radius * sinf(angle)
        );
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Housing
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.25f, 0.8f);
    glVertex2f(0.25f, 0.8f);
    glVertex2f(0.25f, -0.8f);
    glVertex2f(-0.25f, -0.8f);
    glEnd();

    drawCircle(0.0f, 0.5f, 0.15f,
        state == 0 ? 1.0f : 0.3f,
        0.0f, 0.0f);

    drawCircle(0.0f, 0.0f, 0.15f,
        state == 1 ? 1.0f : 0.3f,
        state == 1 ? 1.0f : 0.3f,
        0.0f);

    drawCircle(0.0f, -0.5f, 0.15f,
        0.0f,
        state == 2 ? 1.0f : 0.3f,
        0.0f);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'n' || key == 'N') {
        state = (state + 1) % 3;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 700);
    glutCreateWindow("Ex17 - Traffic Light");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}