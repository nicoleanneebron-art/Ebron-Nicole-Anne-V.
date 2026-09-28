#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdio>

int counter = 0;

void drawText(const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void display() {
    glClearColor(0.07f, 0.11f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    char message[40];
    std::snprintf(message, sizeof(message), "Counter: %d", counter);
    glColor3f(0.85f, 0.95f, 1.0f);
    glRasterPos2f(-0.20f, 0.0f);
    drawText(message);
    glFlush();
}

void timer(int) {
    ++counter;
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q13 - Timer-Driven Counter");
    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
