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
        -0.32f, 0.58f,0.0f, 0.20f,0.70f,1.00f,
         0.32f, 0.58f,0.0f, 0.25f,0.90f,0.65f,
         0.66f, 0.00f,0.0f, 0.95f,0.75f,0.25f,
         0.32f,-0.58f,0.0f, 0.95f,0.40f,0.40f,
        -0.32f,-0.58f,0.0f, 0.70f,0.40f,0.90f,
        -0.66f, 0.00f,0.0f, 0.25f,0.85f,0.85f
    };
    GLubyte indices[] = {0, 1, 2, 3, 4, 5};
    GLsizei stride = 6 * sizeof(GLfloat);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, stride, data);
    glColorPointer(3, GL_FLOAT, stride, data + 3);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 520);
    glutCreateWindow("Q19 - Interleaved and Indexed Hexagon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
