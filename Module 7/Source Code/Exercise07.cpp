#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

float angle = 0.0f;

void drawQuad() {
    glBegin(GL_QUADS);
    glColor3f(0.25f, 0.8f, 0.95f);
    glVertex2f(-0.45f, -0.45f);
    glColor3f(0.3f, 0.9f, 0.65f);
    glVertex2f(0.45f, -0.45f);
    glColor3f(0.7f, 0.6f, 0.95f);
    glVertex2f(0.45f, 0.45f);
    glColor3f(0.3f, 0.7f, 0.85f);
    glVertex2f(-0.45f, 0.45f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    drawQuad();
    glutSwapBuffers();
}

void animateQuad(int value) {
    angle += 2.0f;
    if (angle >= 360.0f) {
        angle = 0.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, animateQuad, value);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q07 - Animated Rotating Quad");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glutDisplayFunc(display);
    glutTimerFunc(16, animateQuad, 0);
    glutMainLoop();
    return 0;
}
