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
         0.00f,  0.00f,
         0.00f,  0.70f,
        -0.67f,  0.22f,
        -0.42f, -0.57f,
         0.42f, -0.57f,
         0.67f,  0.22f
    };
    GLubyte indices[] = {0, 1, 2, 3, 4, 5, 1};

    glColor3f(0.30f, 0.78f, 0.85f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q09 - Indexed Triangle Fan Pentagon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
