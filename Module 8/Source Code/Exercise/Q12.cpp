#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>
float angle = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 1.5, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    GLfloat lightPosition[] = {2.0f, 3.0f, 4.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.4f, -1.0f, 0.0f);
    glVertex3f(1.4f, -1.0f, 0.0f);
    glVertex3f(1.4f, 1.0f, 0.0f);
    glVertex3f(-1.4f, 1.0f, 0.0f);
    glEnd();
    glutSwapBuffers();
}

void animate(int value) {
    angle += 1.0f;
    if (angle >= 360.0f) angle = 0.0f;
    glutPostRedisplay();
    glutTimerFunc(16, animate, value);
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) std::exit(0);
}

void reshape(int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, static_cast<double>(width) / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(900, 650);
    glutCreateWindow("Module 08 - Exercise12 - Front and Back Materials");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    GLfloat front[] = {0.9f, 0.15f, 0.15f, 1.0f};
    GLfloat back[] = {0.15f, 0.35f, 0.95f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front);
    glMaterialfv(GL_BACK, GL_DIFFUSE, back);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, animate, 0);
    glutMainLoop();
    return 0;
}

