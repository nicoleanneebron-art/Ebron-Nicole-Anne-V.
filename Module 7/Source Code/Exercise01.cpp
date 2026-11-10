#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

void drawSquare() {
    glBegin(GL_QUADS);
    glVertex2f(-0.25f, -0.25f);
    glVertex2f(0.25f, -0.25f);
    glVertex2f(0.25f, 0.25f);
    glVertex2f(-0.25f, 0.25f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.4f, 0.0f);
    glColor3f(0.25f, 0.75f, 0.95f);
    drawSquare();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q01 - Translate a Square Upward");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
