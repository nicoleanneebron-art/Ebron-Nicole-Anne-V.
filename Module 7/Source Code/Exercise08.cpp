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
    glVertex2f(-0.2f, -0.2f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.55f, 0.0f, 0.0f);
    glScalef(1.5f, 1.5f, 1.0f);
    glColor3f(0.25f, 0.8f, 0.95f);
    drawSquare();
    glPopMatrix();
    glPushMatrix();
    glScalef(1.5f, 1.5f, 1.0f);
    glTranslatef(0.55f, 0.0f, 0.0f);
    glColor3f(0.35f, 0.9f, 0.6f);
    drawSquare();
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 550);
    glutCreateWindow("Q08 - Transformation Order Comparison");
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
