#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint pointVBO;

void initBuffer() {
    GLfloat p[] = {
        -.8f, 0
    };

    glGenBuffers(1, &pointVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), p, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.3f, .9f, .7f);
    glPointSize(18);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

void timer(int) {
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    GLfloat* p=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    if (p) {
        p[0]+=0.2f;
        if (p[0]>1.0f)p[0]=-1.0f;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitWindowSize(700, 400);
    glutCreateWindow("Q12 - Timer glMapBuffer Moving Point");
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();
    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
