#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.05f, 0.08f, 0.13f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat data[] = {
        -0.65f,-0.55f,0.0f,  0.20f,0.75f,1.00f,
         0.65f,-0.55f,0.0f,  0.30f,0.90f,0.55f,
         0.65f, 0.55f,0.0f,  0.95f,0.65f,0.25f,
        -0.65f, 0.55f,0.0f,  0.70f,0.40f,0.90f
    };
    GLsizei stride = 6 * sizeof(GLfloat);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, stride, data);
    glColorPointer(3, GL_FLOAT, stride, data + 3);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q12 - Interleaved Array Quad");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
