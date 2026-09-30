#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLint triangle[] = {
         0,  70,
       -65, -50,
        65, -50
    };

    glColor3f(0.35f, 0.85f, 0.60f);
    glPushMatrix();
    glScalef(0.01f, 0.01f, 1.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_INT, 0, triangle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q05 - GLint Vertex Data Type");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
