#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat square[] = {
        -0.55f, -0.55f,   0.55f, -0.55f,
         0.55f,  0.55f,  -0.55f,  0.55f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, square);

    glColor3f(0.20f, 0.65f, 0.85f);
    glDrawArrays(GL_QUADS, 0, 4);

    glColor3f(0.85f, 1.0f, 0.95f);
    glLineWidth(5.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q04 - Square Plus Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
