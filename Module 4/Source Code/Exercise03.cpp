#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat lines[] = {
        -0.80f,  0.45f,  -0.15f, -0.35f,
         0.15f,  0.35f,   0.80f, -0.45f
    };

    glColor3f(0.35f, 0.90f, 0.75f);
    glLineWidth(5.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, lines);
    glDrawArrays(GL_LINES, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(650, 450);
    glutCreateWindow("Q03 - Two Lines, One Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
