#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

float backgroundR = 0.1f;
float backgroundG = 0.1f;
float backgroundB = 0.1f;

void display() {
    glClearColor(backgroundR, backgroundG, backgroundB, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
    case 'r':
    case 'R':
        backgroundR = 1.0f; backgroundG = 0.0f; backgroundB = 0.0f;
        std::cout << "Background: Red" << std::endl;
        break;
    case 'g':
    case 'G':
        backgroundR = 0.0f; backgroundG = 1.0f; backgroundB = 0.0f;
        std::cout << "Background: Green" << std::endl;
        break;
    case 'b':
    case 'B':
        backgroundR = 0.0f; backgroundG = 0.0f; backgroundB = 1.0f;
        std::cout << "Background: Blue" << std::endl;
        break;
    default:
        return;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q04 - Keyboard Background Color Switch");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
