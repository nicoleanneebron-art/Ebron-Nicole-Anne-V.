#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0.0f, -0.15f, -5.0f);

    glRotatef(22.0f, 1.0f, 0.0f, 0.0f);

    glRotatef(-35.0f, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);

    glColor3f(0.95f, 0.35f, 0.30f);

    glVertex3f(0.0f, 1.0f, 0.0f);

    glVertex3f(-0.8f, -0.7f, 0.8f);

    glVertex3f(0.8f, -0.7f, 0.8f);

    glColor3f(0.25f, 0.75f, 0.95f);

    glVertex3f(0.0f, 1.0f, 0.0f);

    glVertex3f(0.8f, -0.7f, 0.8f);

    glVertex3f(0.8f, -0.7f, -0.8f);

    glColor3f(0.35f, 0.85f, 0.50f);

    glVertex3f(0.0f, 1.0f, 0.0f);

    glVertex3f(0.8f, -0.7f, -0.8f);

    glVertex3f(-0.8f, -0.7f, -0.8f);

    glColor3f(0.85f, 0.55f, 0.95f);

    glVertex3f(0.0f, 1.0f, 0.0f);

    glVertex3f(-0.8f, -0.7f, -0.8f);

    glVertex3f(-0.8f, -0.7f, 0.8f);

    glEnd();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    if (height == 0) height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(55.0, static_cast<double>(width) / height, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(650, 550);

    glutCreateWindow("Q01 - Immediate-Mode Pyramid");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;

#endif
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
