#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int selectedButton = 0;

void drawText(const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void display() {
    glClearColor(0.08f, 0.10f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (selectedButton == GLUT_LEFT_BUTTON) {
        glColor3f(0.2f, 1.0f, 0.4f);
        glRasterPos2f(-0.28f, 0.0f);
        drawText("Left button text");
    } else if (selectedButton == GLUT_RIGHT_BUTTON) {
        glColor3f(1.0f, 0.25f, 0.25f);
        glRasterPos2f(-0.30f, 0.0f);
        drawText("Right button text");
    }

    glFlush();
}

void mouse(int button, int state, int, int) {
    if (state == GLUT_DOWN &&
        (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON)) {
        selectedButton = button;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(650, 400);
    glutCreateWindow("Q05 - Mouse Button Text Color");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
