#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>
void drawSphere(float x, float shininess) {
    glPushMatrix();
    glTranslatef(x, 0.0f, 0.0f);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glutSolidSphere(0.85, 40, 30);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 2.3, 6.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    GLfloat position[] = {0.0f, 4.0f, 4.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    drawSphere(-1.2f, 8.0f);
    drawSphere(1.2f, 96.0f);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) std::exit(0);
}

void reshape(int width, int height) {
    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, static_cast<double>(width) / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 08 - Exercise05 - Dull vs. Shiny");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

