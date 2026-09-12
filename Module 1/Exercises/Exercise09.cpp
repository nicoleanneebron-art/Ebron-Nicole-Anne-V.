#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black background
    glClear(GL_COLOR_BUFFER_BIT);

    float cellSize = 0.5f; // 4 cells across from -1 to 1

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {

            // Alternate colors
            if ((row + col) % 2 == 0)
                glColor3f(1.0f, 1.0f, 1.0f); // white
            else
                glColor3f(0.0f, 0.0f, 0.0f); // black

            // Compute corners of current square
            float x = -1.0f + col * cellSize;
            float y = 1.0f - row * cellSize;

            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + cellSize, y);
            glVertex2f(x + cellSize, y - cellSize);
            glVertex2f(x, y - cellSize);
            glEnd();
        }
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex09 - 4x4 Checkerboard");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}