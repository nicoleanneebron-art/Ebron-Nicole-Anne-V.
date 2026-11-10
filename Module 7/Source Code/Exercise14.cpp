#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>

bool depthEnabled = true;

void drawTriangle(float z, float red, float green, float blue, float xOffset) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.8f + xOffset, -0.65f, z);
    glVertex3f(0.8f + xOffset, -0.65f, z);
    glVertex3f(xOffset, 0.85f, z);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    drawTriangle(0.5f, 0.3f, 0.85f, 0.65f, -0.15f);
    drawTriangle(0.0f, 0.35f, 0.65f, 0.95f, 0.0f);
    drawTriangle(-0.5f, 0.75f, 0.55f, 0.95f, 0.15f);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    if (key == 'd' || key == 'D') {
        depthEnabled = !depthEnabled;
        if (depthEnabled) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
        std::cout << "Depth test: " << (depthEnabled ? "ON\n" : "OFF\n");
        glutPostRedisplay();
    }
    if (key == 27) {
        std::exit(0);
    }
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
    glutInitWindowSize(750, 600);
    glutCreateWindow("Q14 - Three-Triangle Depth Test");
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
