#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat vertices[] = {
         0.00f,  0.70f,
        -0.70f, -0.55f,
         0.70f, -0.55f
    };
    GLfloat colors[] = {
        0.25f, 0.75f, 1.00f,
        0.30f, 0.90f, 0.55f,
        0.95f, 0.45f, 0.40f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q07 - Vertex and Color Array Triangle");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
