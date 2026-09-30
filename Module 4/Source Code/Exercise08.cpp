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
        -0.72f, 0.48f,  -0.94f, -0.30f,  -0.50f, -0.30f,
         0.00f, 0.48f,  -0.22f, -0.30f,   0.22f, -0.30f,
         0.72f, 0.48f,   0.50f, -0.30f,   0.94f, -0.30f
    };
    GLfloat colors[] = {
        0.2f,0.7f,1.0f, 0.2f,0.7f,1.0f, 0.2f,0.7f,1.0f,
        0.3f,0.9f,0.5f, 0.3f,0.9f,0.5f, 0.3f,0.9f,0.5f,
        0.9f,0.5f,0.3f, 0.9f,0.5f,0.3f, 0.9f,0.5f,0.3f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, 9);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(750, 450);
    glutCreateWindow("Q08 - Three Triangles, One Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
