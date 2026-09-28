#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float grayLevel = 0.20f;
bool pointerInside = false;

void display() {
    glClearColor(grayLevel, grayLevel, grayLevel, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void setPointerState(bool isInside) {
    if (pointerInside == isInside)
        return;

    pointerInside = isInside;
    grayLevel = pointerInside ? 0.75f : 0.20f;
    glutPostRedisplay();
}

void entry(int state) {
    setPointerState(state == GLUT_ENTERED);
}

// Handles the case where the window opens underneath the mouse pointer.
void passiveMotion(int, int) {
    setPointerState(true);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(650, 420);
    glutCreateWindow("Q11 - Entry-Driven Background");
    glutDisplayFunc(display);
    glutEntryFunc(entry);
    glutPassiveMotionFunc(passiveMotion);
    glutMainLoop();
    return 0;
}
