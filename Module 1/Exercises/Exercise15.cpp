#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float squareX = 0.0f;
float squareY = 0.0f;
float size = 0.15f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);

    glBegin(GL_POLYGON);
    glVertex2f(squareX - size, squareY - size);
    glVertex2f(squareX + size, squareY - size);
    glVertex2f(squareX + size, squareY + size);
    glVertex2f(squareX - size, squareY + size);
    glEnd();

    glFlush();
}

void specialKeys(int key, int x, int y) {
    float step = 0.05f;

    switch (key) {
    case GLUT_KEY_LEFT:
        squareX -= step;
        break;
    case GLUT_KEY_RIGHT:
        squareX += step;
        break;
    case GLUT_KEY_UP:
        squareY += step;
        break;
    case GLUT_KEY_DOWN:
        squareY -= step;
        break;
    }

    if (squareX > 1 - size) squareX = 1 - size;
    if (squareX < -1 + size) squareX = -1 + size;
    if (squareY > 1 - size) squareY = 1 - size;
    if (squareY < -1 + size) squareY = -1 + size;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex15 - Moveable Square");

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}