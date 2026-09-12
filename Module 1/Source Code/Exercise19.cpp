#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cstdlib>
using namespace std;

const float colors[6][3] = {
    { 1.0f, 0.0f, 0.0f }, // Red
    { 0.0f, 1.0f, 0.0f }, // Green
    { 0.0f, 0.0f, 1.0f }, // Blue
    { 1.0f, 1.0f, 0.0f }, // Yellow
    { 1.0f, 0.0f, 1.0f }, // Magenta
    { 0.0f, 1.0f, 1.0f }  // Cyan
};

const char* colorNames[6] = {
    "Red", "Green", "Blue", "Yellow", "Magenta", "Cyan"
};

float backgroundColor[3] = { 0.0f, 0.0f, 0.0f };

void display() {
    glClearColor(backgroundColor[0],
        backgroundColor[1],
        backgroundColor[2],
        1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) { // ESC
        exit(0);
    }

    if (key >= '1' && key <= '6') {
        int selectedColor = key - '1';
        backgroundColor[0] = colors[selectedColor][0];
        backgroundColor[1] = colors[selectedColor][1];
        backgroundColor[2] = colors[selectedColor][2];
        cout << colorNames[selectedColor] << endl;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex19 - Colorful Background");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
