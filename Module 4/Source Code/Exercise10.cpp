#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.15f, 0.18f, 0.22f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat vertices[] = {
        -0.90f,-0.30f, -0.90f,0.30f,
        -0.45f,-0.30f, -0.45f,0.30f,
         0.00f,-0.30f,  0.00f,0.30f,
         0.45f,-0.30f,  0.45f,0.30f,
         0.90f,-0.30f,  0.90f,0.30f
    };
    GLubyte quads[4][4] = {
        {0, 2, 3, 1}, {2, 4, 5, 3},
        {4, 6, 7, 5}, {6, 8, 9, 7}
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) glColor3f(0.06f, 0.08f, 0.10f);
        else glColor3f(0.92f, 0.96f, 0.95f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quads[i]);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(750, 400);
    glutCreateWindow("Q10 - Checkerboard Row via glDrawElements");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
