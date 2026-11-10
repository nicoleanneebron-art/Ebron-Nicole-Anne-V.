#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

int windowWidth = 1000;
int windowHeight = 600;

void drawScene() {
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(35.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.3f, 0.8f, 0.95f);
    glutSolidCube(1.8);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int halfWidth = windowWidth / 2;
    glViewport(0, 0, halfWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.2, 2.2, -2.2, 2.2, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    drawScene();
    glViewport(halfWidth, 0, windowWidth - halfWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, static_cast<double>(windowWidth - halfWidth) / windowHeight, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    drawScene();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height == 0 ? 1 : height;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Q16 - Orthographic vs. Perspective");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
