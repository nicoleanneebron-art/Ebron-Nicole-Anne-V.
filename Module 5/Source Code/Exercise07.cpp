#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint zigzagVBO;

void initBuffer() {
    GLfloat points[] = {
        -.9f, -.45f, -.55f, .45f, -.2f, -.45f, .2f, .45f, .55f, -.45f, .9f, .45f
    };

    glGenBuffers(1, &zigzagVBO);
    glBindBuffer(GL_ARRAY_BUFFER, zigzagVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.35f, .9f, .75f);
    glLineWidth(5);

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, zigzagVBO);

    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_LINE_STRIP, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(750, 450);
    glutCreateWindow("Q07 - VBO Line-Strip Zigzag");

    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
