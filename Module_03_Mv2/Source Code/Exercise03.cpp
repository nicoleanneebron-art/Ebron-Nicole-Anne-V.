#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.12f, 0.18f, 0.24f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("My Custom Window");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
