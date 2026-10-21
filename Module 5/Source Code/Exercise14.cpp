#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint pentagonVBO, indexVBO;

void initBuffers() {
    GLfloat p[] = {
        0, 0, 0, .7f, -.67f, .22f, -.42f, -.57f, .42f, -.57f, .67f, .22f
    };

    GLubyte i[] = {
        0, 1, 2, 3, 4, 5, 1
    };

    glGenBuffers(1, &pentagonVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pentagonVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), p, GL_STATIC_DRAW);

    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i), i, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.3f, .78f, .85f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, pentagonVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_BYTE, (void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q14 - Indexed VBO Pentagon Fan");
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffers();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
