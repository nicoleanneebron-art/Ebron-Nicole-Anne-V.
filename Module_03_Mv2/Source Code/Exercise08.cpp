#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float squareX = 0.0f;
const float HALF_SIZE = 0.1f;

void display() {
    glClearColor(0.07f, 0.11f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.25f, 0.80f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(squareX - HALF_SIZE, -HALF_SIZE);
    glVertex2f(squareX + HALF_SIZE, -HALF_SIZE);
    glVertex2f(squareX + HALF_SIZE, HALF_SIZE);
    glVertex2f(squareX - HALF_SIZE, HALF_SIZE);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key == 'a' || key == 'A')
        squareX -= 0.08f;
    else if (key == 'd' || key == 'D')
        squareX += 0.08f;
    else
        return;

    const float centerLimit = 1.0f - HALF_SIZE;
    if (squareX < -centerLimit) squareX = -centerLimit;
    if (squareX > centerLimit) squareX = centerLimit;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q08 - Clamped Keyboard Movement");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
