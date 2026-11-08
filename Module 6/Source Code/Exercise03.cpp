#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>

float inputPoint[2] = {
    0.25f, 0.20f
};

float outputPoint[2];

void calculateScalarProduct() {
    float scalarMatrix[4] = {
        2.0f, 0.0f, 0.0f, 2.0f
    };

    outputPoint[0] = scalarMatrix[0] * inputPoint[0] + scalarMatrix[1] * inputPoint[1];

    outputPoint[1] = scalarMatrix[2] * inputPoint[0] + scalarMatrix[3] * inputPoint[1];

    std::cout << "Before: (" << inputPoint[0] << ", " << inputPoint[1] << ")\n";

    std::cout << "After:  (" << outputPoint[0] << ", " << outputPoint[1] << ")\n";
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(14.0f);

    glBegin(GL_POINTS);

    glColor3f(0.25f, 0.75f, 1.0f);

    glVertex2fv(inputPoint);

    glColor3f(0.35f, 0.95f, 0.55f);

    glVertex2fv(outputPoint);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(600, 500);

    glutCreateWindow("Q03 - Scalar Product Matrix");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;

#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);

    calculateScalarProduct();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
