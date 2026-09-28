#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

bool inside = false;
float orbitAngle = 0.0f;
int previousTime = 0;

void display() {
    glClearColor(0.06f, 0.10f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float x = 0.55f * std::cos(orbitAngle);
    float y = 0.55f * std::sin(orbitAngle);
    glColor3f(0.30f, 0.85f, 0.72f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.09f, y - 0.09f);
    glVertex2f(x + 0.09f, y - 0.09f);
    glVertex2f(x + 0.09f, y + 0.09f);
    glVertex2f(x - 0.09f, y + 0.09f);
    glEnd();
    glutSwapBuffers();
}

void entry(int state) {
    inside = (state == GLUT_ENTERED);
    previousTime = glutGet(GLUT_ELAPSED_TIME);
}

void idle() {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float seconds = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;

    if (inside) {
        orbitAngle += 1.5f * seconds;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(650, 500);
    glutCreateWindow("Q18 - Entry and Idle Freeze Combo");
    previousTime = glutGet(GLUT_ELAPSED_TIME);
    glutDisplayFunc(display);
    glutEntryFunc(entry);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
