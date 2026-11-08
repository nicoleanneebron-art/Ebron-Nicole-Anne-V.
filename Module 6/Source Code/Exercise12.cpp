#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint triangleVBO=0;

void translate(float* v, float x, float y, float z) {
    float m[16]={
        1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1
    };

    float px=v[0], py=v[1], pz=v[2], w=1;

    v[0]=m[0]*px+m[4]*py+m[8]*pz+m[12]*w;

    v[1]=m[1]*px+m[5]*py+m[9]*pz+m[13]*w;

    v[2]=m[2]*px+m[6]*py+m[10]*pz+m[14]*w;
}

void initBuffer() {
    GLfloat p[] = {
        0, -.55f, 0, -.3f, -.9f, 0, .3f, -.9f, 0
    };

    glGenBuffers(1, &triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(p), p, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.3f, .85f, .65f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

void modifyPolygon(int) {
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    GLfloat* p=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    if (p) {
        for (int i=0;i<9;i+=3)translate(&p[i], 0, .18f, 0);
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(1000, modifyPolygon, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 550);
    glutCreateWindow("Q12 - Timer translate Animation");

#ifndef __APPLE__
    if (glewInit()!=GLEW_OK)return 1;

#endif
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();
    glutDisplayFunc(display);
    glutTimerFunc(1000, modifyPolygon, 0);
    glutMainLoop();
    return 0;
}
