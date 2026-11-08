#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <cmath>

GLuint quadVBO=0;
const float PI=3.14159265f;
const GLsizeiptr POS_BYTES=12*sizeof(GLfloat);

void rotateY(float* v, float degrees) {
    float a=degrees*PI/180;
    float x=v[0], z=v[2];
    v[0]=cosf(a)*x+sinf(a)*z;
    v[2]=-sinf(a)*x+cosf(a)*z;
}

void initBuffer() {
    GLfloat p[] = {
        -.7f, -.55f, 0, .7f, -.55f, 0, .7f, .55f, 0, -.7f, .55f, 0
    };

    GLfloat c[] = {
        1, .3f, .3f, .3f, 1, .5f, .3f, .65f, 1, 1, .8f, .25f
    };

    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, POS_BYTES+sizeof(c), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, POS_BYTES, p);
    glBufferSubData(GL_ARRAY_BUFFER, POS_BYTES, sizeof(c), c);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -3);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glColorPointer(3, GL_FLOAT, 0, (void*)POS_BYTES);
    glDrawArrays(GL_QUADS, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}

void timer(int) {
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    GLfloat* p=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if (p) {
        for (int i=0;i<12;i+=3)rotateY(&p[i], 15);
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

void monitorKeyboard(unsigned char key, int, int) {
    if (key==27) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &quadVBO);
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
    glutInitWindowSize(650, 550);
    glutCreateWindow("Q19 - Continuous Y Rotation");

#ifndef __APPLE__
    if (glewInit()!=GLEW_OK)return 1;

#endif
    glEnable(GL_DEPTH_TEST);
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(monitorKeyboard);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
