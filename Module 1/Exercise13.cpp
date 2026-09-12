#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void drawRect(float x0, float y0, float x1, float y1) {
    glBegin(GL_POLYGON);
    glVertex2f(x0, y0);
    glVertex2f(x1, y0);
    glVertex2f(x1, y1);
    glVertex2f(x0, y1);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);

    // Stem
    drawRect(-0.6f, -0.7f, -0.4f, 0.7f);

    // Top bar
    drawRect(-0.6f, 0.5f, 0.3f, 0.7f);

    // Middle bar
    drawRect(-0.6f, 0.0f, 0.1f, 0.2f);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex13 - Letter F from Rectangles");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}