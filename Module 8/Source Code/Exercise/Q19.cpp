#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>
void setMaterial(float shininess, float red, float green, float blue) {
    GLfloat diffuse[] = {red, green, blue, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 3.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    GLfloat leftLight[] = {-3.0f, 4.0f, 3.0f, 1.0f};
    GLfloat rightLight[] = {3.0f, 3.0f, 2.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, leftLight);
    glLightfv(GL_LIGHT1, GL_POSITION, rightLight);
    glPushMatrix();
    glTranslatef(-1.5f, 0.0f, 0.0f);
    setMaterial(8.0f, 0.25f, 0.7f, 0.85f);
    glutSolidSphere(1.0, 40, 30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5f, 0.0f, 0.0f);
    setMaterial(96.0f, 0.75f, 0.45f, 0.9f);
    glutSolidTeapot(1.0);
    glPopMatrix();
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
    glutCreateWindow("Module 08 - Exercise19 - Two-Material Showroom");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    GLfloat warm[] = {1.0f, 0.65f, 0.35f, 1.0f};
    GLfloat cool[] = {0.3f, 0.5f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, warm);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, cool);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

