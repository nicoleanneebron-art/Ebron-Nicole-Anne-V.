#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint pentagonVBO=0;

const GLsizeiptr POS_BYTES=10*sizeof(GLfloat);

void initBuffer() {
    GLfloat p[] = {
        0, .72f, -.68f, .22f, -.42f, -.58f, .42f, -.58f, .68f, .22f
    };

    GLfloat c[] = {
        1, .3f, .3f, .3f, 1, .45f, .25f, .65f, 1, .8f, .35f, 1, 1, .8f, .25f
    };

    glGenBuffers(1, &pentagonVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pentagonVBO);

    glBufferData(GL_ARRAY_BUFFER, POS_BYTES+sizeof(c), nullptr, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, POS_BYTES, p);
    glBufferSubData(GL_ARRAY_BUFFER, POS_BYTES, sizeof(c), c);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, pentagonVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glColorPointer(3, GL_FLOAT, 0, (void*)POS_BYTES);

    glBegin(GL_POLYGON);
    for (int i=0;i<5;++i)glArrayElement(i);
    glEnd();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 520);
    glutCreateWindow("Q14 - glArrayElement Loop Pentagon");

#ifndef __APPLE__
    if (glewInit()!=GLEW_OK)return 1;

#endif
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
