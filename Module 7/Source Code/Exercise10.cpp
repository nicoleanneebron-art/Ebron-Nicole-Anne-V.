#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>

bool wideView = true;
int windowWidth = 800;
int windowHeight = 600;

void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double fieldOfView = wideView ? 90.0 : 30.0;
    gluPerspective(fieldOfView, static_cast<double>(windowWidth) / windowHeight, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setProjection();
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(35.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.3f, 0.8f, 0.95f);
    glutSolidCube(1.5);
    glutSwapBuffers();
}

void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height == 0 ? 1 : height;
    glViewport(0, 0, windowWidth, windowHeight);
}

void keyboard(unsigned char key, int, int) {
    if (key == 'v' || key == 'V') {
        wideView = !wideView;
        std::cout << (wideView ? "Wide FOV: 90 degrees\n" : "Narrow FOV: 30 degrees\n");
        glutPostRedisplay();
    }
    if (key == 27) {
        std::exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Q10 - Wide vs. Narrow Field of View");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
