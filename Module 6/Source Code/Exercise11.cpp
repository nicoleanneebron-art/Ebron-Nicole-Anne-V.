#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint faceVBO=0;

const GLsizeiptr POS_BYTES=12*sizeof(GLfloat);

void initBuffer() {
    GLfloat p[] = {
        -.65f, -.5f, 0, .65f, -.5f, 0, .65f, .5f, 0, -.65f, .5f, 0
    };

    GLfloat c[] = {
        .2f, .7f, 1, .3f, .9f, .55f, .95f, .65f, .25f, .7f, .4f, .9f
    };

    glGenBuffers(1, &faceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, faceVBO);

    glBufferData(GL_ARRAY_BUFFER, POS_BYTES+sizeof(c), nullptr, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, POS_BYTES, p);

    glBufferSubData(GL_ARRAY_BUFFER, POS_BYTES, sizeof(c), c);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, faceVBO);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glColorPointer(3, GL_FLOAT, 0, (void*)POS_BYTES);
    glDrawArrays(GL_QUADS, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q11 - Color Cube Face via SubData");

#ifndef __APPLE__
    if (glewInit()!=GLEW_OK)return 1;

#endif
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
