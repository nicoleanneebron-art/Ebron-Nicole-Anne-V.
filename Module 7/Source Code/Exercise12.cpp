#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <cmath>

float orbitAngle = 0.0f;
const float PI = 3.14159265f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float radians = orbitAngle * PI / 180.0f;
    float eyeX = sinf(radians) * 4.0f;
    float eyeZ = cosf(radians) * 4.0f;
    gluLookAt(eyeX, 2.0f, eyeZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.25f, 0.8f, 0.95f);
    glBegin(GL_QUADS);
    glVertex3f(-1.2f, 0.0f, -1.2f);
    glVertex3f(1.2f, 0.0f, -1.2f);
    glVertex3f(1.2f, 0.0f, 1.2f);
    glVertex3f(-1.2f, 0.0f, 1.2f);
    glEnd();
    glutSwapBuffers();
}

void animateCamera(int value) {
    orbitAngle += 1.0f;
    if (orbitAngle >= 360.0f) {
        orbitAngle = 0.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, animateCamera, value);
}

void reshape(int width, int height) {
    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, static_cast<double>(width) / height, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q12 - Orbiting Camera");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, animateCamera, 0);
    glutMainLoop();
    return 0;
}
