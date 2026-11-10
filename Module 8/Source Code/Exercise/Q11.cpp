#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>
void drawSpotSphere(float x, float cutoff) {
    GLfloat position[] = {x, 3.0f, 2.0f, 1.0f};
    GLfloat direction[] = {0.0f, -3.0f, -2.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
    glPushMatrix();
    glTranslatef(x, 0.0f, 0.0f);
    glutSolidSphere(0.75, 36, 28);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 3.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawSpotSphere(-2.2f, 15.0f);
    drawSpotSphere(0.0f, 30.0f);
    drawSpotSphere(2.2f, 60.0f);
    glutSwapBuffers();
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
    glutCreateWindow("Module 08 - Exercise11 - Spotlight Cutoff");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 8.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

