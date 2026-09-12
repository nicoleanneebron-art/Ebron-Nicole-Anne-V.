#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const int STRIPE_COUNT = 10;
const float PI = 3.14159265f;
float windowAspect = 800.0f / 500.0f;

void reshape(int width, int height) {
    if (height == 0)
        height = 1;

    windowAspect = static_cast<float>(width) / height;
    glViewport(0, 0, width, height);
}

void drawFilledStar(float cx, float cy, float outerR, float innerR) {
    // A star is concave, so a triangle fan fills it more reliably than
    // GL_POLYGON. Dividing X by the aspect ratio prevents stretching.
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);

    for (int i = 0; i <= 10; i++) {
        int point = i % 10;
        float angle = PI / 2.0f + point * PI / 5.0f;
        float radius = (point % 2 == 0) ? outerR : innerR;

        glVertex2f(
            cx + radius * cosf(angle) / windowAspect,
            cy + radius * sinf(angle)
        );
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float stripeHeight = 2.0f / STRIPE_COUNT;

    for (int i = 0;i < STRIPE_COUNT;i++) {

        if (i % 2 == 0)
            glColor3f(0, 0, 1);
        else
            glColor3f(0, 0.9, 0);

        float top = 1.0f - i * stripeHeight;
        float bottom = top - stripeHeight;

        glBegin(GL_POLYGON);
        glVertex2f(-1.0f, top);
        glVertex2f(1.0f, top);
        glVertex2f(1.0f, bottom);
        glVertex2f(-1.0f, bottom);
        glEnd();
    }

    // Filled star
    glColor3f(1.0f, 1.0f, 0.0f);

    float cx = -0.7f;
    float cy = 0.7f;
    float outerR = 0.18f;
    float innerR = 0.08f;

    drawFilledStar(cx, cy, outerR, innerR);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Ex20 - Procedural Flag");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
