#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <cmath>

int windowWidth = 1000;
int windowHeight = 600;
float orbitAngle = 0.0f;
const float PI = 3.14159265f;

void drawScene() {
    glColor3f(0.25f, 0.8f, 0.95f);
    glutSolidCube(1.4);
    glPushMatrix();
    glTranslatef(-1.6f, -0.7f, -0.6f);
    glColor3f(0.35f, 0.9f, 0.6f);
    glutSolidTeapot(0.55);
    glPopMatrix();
    glColor3f(0.55f, 0.65f, 0.75f);
    glBegin(GL_LINES);
    for (int value = -3; value <= 3; ++value) {
        glVertex3f(static_cast<float>(value), -1.0f, -3.0f);
        glVertex3f(static_cast<float>(value), -1.0f, 3.0f);
        glVertex3f(-3.0f, -1.0f, static_cast<float>(value));
        glVertex3f(3.0f, -1.0f, static_cast<float>(value));
    }
    glEnd();
}

void setPerspective(int x, int width) {
    glViewport(x, 0, width, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, static_cast<double>(width) / windowHeight, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int halfWidth = windowWidth / 2;
    setPerspective(0, halfWidth);
    glLoadIdentity();
    gluLookAt(4.0, 2.8, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawScene();
    setPerspective(halfWidth, windowWidth - halfWidth);
    glLoadIdentity();
    float radians = orbitAngle * PI / 180.0f;
    float eyeX = sinf(radians) * 6.0f;
    float eyeZ = cosf(radians) * 6.0f;
    gluLookAt(eyeX, 2.8, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawScene();
    glutSwapBuffers();
}

void animateCamera(int value) {
    orbitAngle += 0.8f;
    if (orbitAngle >= 360.0f) {
        orbitAngle = 0.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, animateCamera, value);
}

void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height == 0 ? 1 : height;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Q19 - Two Viewports and Two Cameras");
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
