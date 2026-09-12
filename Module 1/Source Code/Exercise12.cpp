#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);

    // Shaft
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(-0.7f, 0.0f);
    glVertex2f(0.4f, 0.0f);
    glEnd();

    // Arrowhead
    glBegin(GL_TRIANGLES);
    glVertex2f(0.4f, 0.15f);
    glVertex2f(0.4f, -0.15f);
    glVertex2f(0.8f, 0.0f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex12 - Arrow");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}