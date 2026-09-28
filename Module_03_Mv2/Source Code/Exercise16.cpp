#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

bool dragging = false;
float squareX = 0.0f;
float squareY = 0.0f;

void toOpenGL(int x, int y, float& openGLX, float& openGLY) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    openGLX = 2.0f * x / width - 1.0f;
    openGLY = 1.0f - 2.0f * y / height;
}

void display() {
    glClearColor(0.07f, 0.11f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const float halfSize = 0.12f;
    glColor3f(0.30f, 0.82f, 0.72f);
    glBegin(GL_QUADS);
    glVertex2f(squareX - halfSize, squareY - halfSize);
    glVertex2f(squareX + halfSize, squareY - halfSize);
    glVertex2f(squareX + halfSize, squareY + halfSize);
    glVertex2f(squareX - halfSize, squareY + halfSize);
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON) return;

    dragging = (state == GLUT_DOWN);
    if (dragging) {
        toOpenGL(x, y, squareX, squareY);
        glutPostRedisplay();
    }
}

void motion(int x, int y) {
    if (!dragging) return;
    toOpenGL(x, y, squareX, squareY);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q16 - Click-and-Drag Square");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}
