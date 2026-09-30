#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat points[] = {
        -0.55f,  0.55f,   0.55f,  0.55f,
         0.00f,  0.00f,
        -0.55f, -0.55f,   0.55f, -0.55f
    };

    glColor3f(0.30f, 0.85f, 0.75f);
    glPointSize(12.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, points);
    glDrawArrays(GL_POINTS, 0, 5);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q01 - Vertex Array X-Pattern Points");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
