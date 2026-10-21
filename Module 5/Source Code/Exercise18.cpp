#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint dataVBO, indexVBO;

void initBuffers() {
    GLfloat d[] = {
        -.32f, .58f, 0, .2f, .7f, 1, .32f, .58f, 0, .25f, .9f, .6f, .66f, 0, 0, .95f, .75f, .25f, .32f, -.58f, 0, .95f, .4f, .4f, -.32f, -.58f, 0, .7f, .4f, .9f, -.66f, 0, 0, .25f, .85f, .85f
    };

    GLubyte i[] = {
        0, 1, 2, 3, 4, 5
    };

    glGenBuffers(1, &dataVBO);
    glBindBuffer(GL_ARRAY_BUFFER, dataVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(d), d, GL_STATIC_DRAW);
    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i), i, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    GLsizei s=6*sizeof(GLfloat);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, dataVBO);
    glVertexPointer(3, GL_FLOAT, s, (void*)0);
    glColorPointer(3, GL_FLOAT, s, (void*)(3*sizeof(GLfloat)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, (void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitWindowSize(600, 520);
    glutCreateWindow("Q18 - Interleaved Indexed VBO Hexagon");
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffers();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
