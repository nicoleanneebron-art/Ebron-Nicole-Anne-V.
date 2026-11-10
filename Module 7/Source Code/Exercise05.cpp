#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.3f, 0.85f, 0.7f);
    glBegin(GL_TRIANGLES);
    glVertex2f(1.2f, 0.7f);
    glVertex2f(2.8f, 0.7f);
    glVertex2f(2.0f, 2.3f);
    glEnd();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 4.0, 0.0, 3.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q05 - Non-Symmetric glOrtho Box");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
