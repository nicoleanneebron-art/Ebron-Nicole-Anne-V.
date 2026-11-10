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
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(-0.3f, 0.3f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glScalef(2.0f, 0.5f, 1.0f);
    glColor3f(0.35f, 0.75f, 0.95f);
    drawSquare();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(650, 500);
    glutCreateWindow("Q03 - Non-Uniform Scaling");
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
