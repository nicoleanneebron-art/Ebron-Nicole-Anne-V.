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
        -0.65f, -0.50f,
         0.65f, -0.50f,
         0.00f,  0.65f
    };
    // Visits top, left, then right instead of storage order 0, 1, 2.
    GLubyte indices[] = {2, 0, 1};

    glColor3f(0.90f, 0.60f, 0.30f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q06 - glDrawElements Index Order");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
