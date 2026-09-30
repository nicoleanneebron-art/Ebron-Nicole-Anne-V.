#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.05f, 0.08f, 0.13f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat vertices[] = {
        -0.80f,-0.70f, -0.80f,-0.40f,
        -0.30f,-0.70f, -0.30f,-0.40f,
        -0.30f,-0.70f, -0.30f,-0.05f,
         0.20f,-0.70f,  0.20f,-0.05f,
         0.20f,-0.70f,  0.20f, 0.35f,
         0.70f,-0.70f,  0.70f, 0.35f
    };
    GLfloat colors[] = {
        0.20f,0.65f,1.0f, 0.20f,0.65f,1.0f,
        0.20f,0.65f,1.0f, 0.20f,0.65f,1.0f,
        0.25f,0.85f,0.55f, 0.25f,0.85f,0.55f,
        0.25f,0.85f,0.55f, 0.25f,0.85f,0.55f,
        0.95f,0.65f,0.25f, 0.95f,0.65f,0.25f,
        0.95f,0.65f,0.25f, 0.95f,0.65f,0.25f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUAD_STRIP, 0, 12);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 550);
    glutCreateWindow("Q14 - Colored Quad Strip Staircase");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
