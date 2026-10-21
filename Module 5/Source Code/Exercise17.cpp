#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <cmath>

const int DASHES=30;
const float PI=3.14159265f;
GLuint ringVBO;

void initBuffer() {
    GLfloat p[DASHES*2*2];
    for (int i=0;i<DASHES;i++) {
        float a=2*PI*i/DASHES;
        int k=i*4;
        p[k]=.62f*cosf(a);
        p[k+1]=.62f*sinf(a);
        p[k+2]=.82f*cosf(a);
        p[k+3]=.82f*sinf(a);
    }

    glGenBuffers(1, &ringVBO);
    glBindBuffer(GL_ARRAY_BUFFER, ringVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), p, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.3f, .85f, .72f);
    glLineWidth(4);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, ringVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_LINES, 0, DASHES*2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q17 - Procedural 30-Dash VBO Ring");
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
