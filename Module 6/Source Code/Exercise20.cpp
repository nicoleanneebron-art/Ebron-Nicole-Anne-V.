#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <cmath>

GLuint cubeVBO=0;
const int COUNT=12;
const GLsizeiptr POS_BYTES=COUNT*3*sizeof(GLfloat);
const float PI=3.14159265f;

void rotateZ(float* v, float degrees) {
    float a=degrees*PI/180;
    float x=v[0], y=v[1];
    v[0]=cosf(a)*x-sinf(a)*y;
    v[1]=sinf(a)*x+cosf(a)*y;
}

void translate(float* v, float x, float y, float z) {
    v[0]+=x;
    v[1]+=y;
    v[2]+=z;
}

void initBuffer() {
    GLfloat p[] = {
        -.6f, -.6f, .6f, .6f, -.6f, .6f, .6f, .6f, .6f, -.6f, .6f, .6f, .6f, -.6f, .6f, .6f, -.6f, -.6f, .6f, .6f, -.6f, .6f, .6f, .6f, -.6f, .6f, .6f, .6f, .6f, .6f, .6f, .6f, -.6f, -.6f, .6f, -.6f
    };

    GLfloat c[COUNT*3];
    for (int i=0;i<COUNT;++i) {
        c[i*3]=(i%3==0)?1:.25f;
        c[i*3+1]=(i%3==1)?1:.45f;
        c[i*3+2]=(i%3==2)?1:.75f;
    }

    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, POS_BYTES+sizeof(c), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, POS_BYTES, p);
    glBufferSubData(GL_ARRAY_BUFFER, POS_BYTES, sizeof(c), c);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -4);
    glRotatef(20, 1, 0, 0);
    glRotatef(-30, 0, 1, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glColorPointer(3, GL_FLOAT, 0, (void*)POS_BYTES);
    glDrawArrays(GL_QUADS, 0, COUNT);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}

void timer(int) {
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    GLfloat* p=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if (p) {
        for (int i=0;i<COUNT*3;i+=3) {
            rotateZ(&p[i], 8);
            translate(&p[i], .025f, .018f, 0);
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

void keyboard(unsigned char key, int, int) {
    if (key==27) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &cubeVBO);
        std::exit(0);
    }
}

void reshape(int w, int h) {
    if (h==0)h=1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55, (double)w/h, 1, 20);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(680, 560);
    glutCreateWindow("Q20 - Rotating and Drifting Color Cube");

#ifndef __APPLE__
    if (glewInit()!=GLEW_OK)return 1;

#endif
    glEnable(GL_DEPTH_TEST);
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
