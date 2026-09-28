#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdio>

int elapsedSeconds = 0;
bool running = false;

void drawText(const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void display() {
    glClearColor(0.06f, 0.10f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    char message[64];
    std::snprintf(message, sizeof(message), "Stopwatch: %d seconds", elapsedSeconds);
    glColor3f(running ? 0.35f : 0.75f, running ? 0.95f : 0.80f, 0.80f);
    glRasterPos2f(-0.35f, 0.0f);
    drawText(message);
    glFlush();
}

void mouse(int button, int state, int, int) {
    if (state != GLUT_DOWN) return;
    if (button == GLUT_LEFT_BUTTON)
        running = true;
    else if (button == GLUT_RIGHT_BUTTON)
        running = false;
    glutPostRedisplay();
}

void timer(int) {
    if (running) {
        ++elapsedSeconds;
        glutPostRedisplay();
    }
    glutTimerFunc(1000, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q17 - Mouse-Controlled Stopwatch");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
