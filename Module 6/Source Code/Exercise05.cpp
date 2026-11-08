#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>

void printMatrixSum() {
    float a[4] = {
        1.0f, 2.0f, 3.0f, 4.0f
    };

    float b[4] = {
        5.0f, 6.0f, 7.0f, 8.0f
    };

    float result[4];

    for (int i = 0; i < 4; ++i) result[i] = a[i] + b[i];

    std::cout << "Matrix sum:\n";

    std::cout << result[0] << " " << result[1] << "\n";

    std::cout << result[2] << " " << result[3] << "\n";
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.25f, 0.75f, 0.90f);

    glBegin(GL_QUADS);

    glVertex2f(-0.5f, -0.4f);

    glVertex2f(0.5f, -0.4f);

    glVertex2f(0.5f, 0.4f);

    glVertex2f(-0.5f, 0.4f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(600, 450);

    glutCreateWindow("Q05 - Matrix Addition");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;

#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);

    printMatrixSum();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
