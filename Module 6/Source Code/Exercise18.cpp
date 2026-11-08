#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint combinedVBO=0;

const GLsizeiptr P1=9*sizeof(GLfloat), P2=12*sizeof(GLfloat), C1=9*sizeof(GLfloat), C2=12*sizeof(GLfloat);

const GLintptr P1_OFFSET=0, P2_OFFSET=P1, C1_OFFSET=P1+P2, C2_OFFSET=P1+P2+C1;

void initBuffer() {
    GLfloat pyramid[] = {
        -.85f, -.45f, 0, -.25f, -.45f, 0, -.55f, .55f, 0
    };

    GLfloat cube[] = {
        .15f, -.45f, 0, .85f, -.45f, 0, .85f, .45f, 0, .15f, .45f, 0
    };

    GLfloat pyramidColor[] = {
        1, .3f, .3f, .3f, 1, .5f, .3f, .65f, 1
    };

    GLfloat cubeColor[] = {
        .25f, .75f, 1, .3f, .9f, .55f, .95f, .65f, .25f, .7f, .4f, .9f
    };

    glGenBuffers(1, &combinedVBO);
    glBindBuffer(GL_ARRAY_BUFFER, combinedVBO);
    glBufferData(GL_ARRAY_BUFFER, P1+P2+C1+C2, nullptr, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, P1_OFFSET, P1, pyramid);
    glBufferSubData(GL_ARRAY_BUFFER, P2_OFFSET, P2, cube);

    glBufferSubData(GL_ARRAY_BUFFER, C1_OFFSET, C1, pyramidColor);
    glBufferSubData(GL_ARRAY_BUFFER, C2_OFFSET, C2, cubeColor);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, combinedVBO);

    glVertexPointer(3, GL_FLOAT, 0, (void*)P1_OFFSET);
    glColorPointer(3, GL_FLOAT, 0, (void*)C1_OFFSET);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexPointer(3, GL_FLOAT, 0, (void*)P2_OFFSET);
    glColorPointer(3, GL_FLOAT, 0, (void*)C2_OFFSET);
    glDrawArrays(GL_QUADS, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(750, 500);
    glutCreateWindow("Q18 - Two Shapes One Combined Buffer");

#ifndef __APPLE__
    if (glewInit()!=GLEW_OK)return 1;

#endif
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
