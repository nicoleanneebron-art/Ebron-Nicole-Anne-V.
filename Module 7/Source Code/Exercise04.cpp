#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

void drawQuad() {
    glBegin(GL_QUADS);
    glVertex2f(-0.22f, -0.22f);
    glVertex2f(0.22f, -0.22f);
    glVertex2f(0.22f, 0.22f);
    glVertex2f(-0.22f, 0.22f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.65f, 0.0f, 0.0f);
    glColor3f(0.25f, 0.75f, 0.95f);
    drawQuad();
    glPopMatrix();
    glPushMatrix();
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.35f, 0.9f, 0.65f);
    drawQuad();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.65f, 0.0f, 0.0f);
    glColor3f(0.65f, 0.55f, 0.95f);
    drawQuad();
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Q04 - Three Quads, One Rotated");
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
