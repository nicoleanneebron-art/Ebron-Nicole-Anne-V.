#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float shapeY = 0.0f;

void display() {
    glClearColor(0.07f, 0.11f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.30f, 0.78f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(-0.12f, shapeY - 0.12f);
    glVertex2f(0.12f, shapeY - 0.12f);
    glVertex2f(0.12f, shapeY + 0.12f);
    glVertex2f(-0.12f, shapeY + 0.12f);
    glEnd();
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key == 'w' || key == 'W')
        shapeY += 0.08f;
    else if (key == 's' || key == 'S')
        shapeY -= 0.08f;
    else
        return;

    if (shapeY > 0.88f) shapeY = 0.88f;
    if (shapeY < -0.88f) shapeY = -0.88f;
    glutPostRedisplay();
}

void mouse(int, int state, int, int) {
    if (state == GLUT_DOWN) {
        shapeY = 0.0f;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(650, 500);
    glutCreateWindow("Q14 - Keyboard and Mouse Combo");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
