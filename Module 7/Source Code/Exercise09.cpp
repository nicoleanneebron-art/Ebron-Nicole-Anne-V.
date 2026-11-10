#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

void drawSegment(float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, -0.1f);
    glVertex2f(0.9f, -0.1f);
    glVertex2f(0.9f, 0.1f);
    glVertex2f(0.0f, 0.1f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-0.8f, -0.25f, 0.0f);
    glPushMatrix();
    glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
    drawSegment(0.25f, 0.75f, 0.95f);
    glTranslatef(0.9f, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
    drawSegment(0.35f, 0.9f, 0.6f);
    glTranslatef(0.9f, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(-55.0f, 0.0f, 0.0f, 1.0f);
    drawSegment(0.75f, 0.55f, 0.95f);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(850, 600);
    glutCreateWindow("Q09 - Three-Segment Hierarchical Chain");
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
