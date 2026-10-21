#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint leftTriangleVBO, rightTriangleVBO;

void upload(GLuint& id, const GLfloat* data) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);

    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(GLfloat), data, GL_STATIC_DRAW);
}

void initBuffers() {
    GLfloat left[] = {
        -.55f, .55f, -.9f, -.5f, -.2f, -.5f
    };

    GLfloat right[] = {
        .55f, .55f, .2f, -.5f, .9f, -.5f
    };

    upload(leftTriangleVBO, left);
    upload(rightTriangleVBO, right);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawTriangle(GLuint id, float r, float g, float b) {
    glColor3f(r, g, b);
    glBindBuffer(GL_ARRAY_BUFFER, id);

    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    drawTriangle(leftTriangleVBO, .25f, .72f, .95f);
    drawTriangle(rightTriangleVBO, .3f, .88f, .55f);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q05 - Two Separate VBOs");

    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffers();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
