#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat hexagon[] = {
        -0.30f,  0.55f,   0.30f,  0.55f,
         0.62f,  0.00f,   0.30f, -0.55f,
        -0.30f, -0.55f,  -0.62f,  0.00f
    };

    glColor3f(0.25f, 0.70f, 0.90f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, hexagon);
    glDrawArrays(GL_POLYGON, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q02 - Filled Hexagon via Vertex Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
