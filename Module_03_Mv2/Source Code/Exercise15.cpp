#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdio>

int secondsRemaining = 30;
bool timeIsUp = false;

void drawText(const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void display() {
    glClearColor(0.07f, 0.10f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.90f, 0.96f, 1.0f);

    if (timeIsUp) {
        glRasterPos2f(-0.16f, 0.0f);
        drawText("Time's up!");
    } else {
        char message[40];
        std::snprintf(message, sizeof(message), "Time: %d", secondsRemaining);
        glRasterPos2f(-0.14f, 0.0f);
        drawText(message);
    }
    glFlush();
}

void timer(int) {
    --secondsRemaining;
    if (secondsRemaining <= 0) {
        secondsRemaining = 0;
        timeIsUp = true;
    } else {
        glutTimerFunc(1000, timer, 0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q15 - 30-Second Countdown Timer");
    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
