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
         0.0f, 0.0f,
        -0.12f,0.72f,  0.38f,0.28f,
         0.72f,0.12f,  0.28f,-0.38f,
         0.12f,-0.72f, -0.38f,-0.28f,
        -0.72f,-0.12f, -0.28f,0.38f
    };
    GLubyte indices[] = {
        0,1,2,  0,3,4,  0,5,6,  0,7,8
    };

    glColor3f(0.30f, 0.80f, 0.82f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q13 - Pinwheel via glDrawElements");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
