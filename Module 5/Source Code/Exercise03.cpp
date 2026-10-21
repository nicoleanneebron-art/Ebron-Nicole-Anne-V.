#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint hexagonVBO;

void initBuffer() {
    GLfloat hexagon[] = {
        -.3f, .58f, .3f, .58f, .65f, 0, .3f, -.58f, -.3f, -.58f, -.65f, 0
    };

    glGenBuffers(1, &hexagonVBO);
    glBindBuffer(GL_ARRAY_BUFFER, hexagonVBO);

    // Uploaded once and reused without changes, so GL_STATIC_DRAW is the best hint.
    glBufferData(GL_ARRAY_BUFFER, sizeof(hexagon), hexagon, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.25f, .72f, .9f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, hexagonVBO);

    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_POLYGON, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q03 - Static VBO Hexagon");

    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
