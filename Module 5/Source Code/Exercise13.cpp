#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint triangleVBO, quadVBO;

void initBuffers() {
    GLfloat t[] = {
        -.55f, .55f, -.9f, -.45f, -.2f, -.45f
    };

    GLfloat q[] = {
        .2f, -.45f, .9f, -.45f, .9f, .45f, .2f, .45f
    };

    glGenBuffers(1, &triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(t), t, GL_STATIC_DRAW);

    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(q), q, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(.25f, .7f, .95f);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glColor3f(.3f, .88f, .55f);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_QUADS, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

void monitorKeyboard(unsigned char key, int, int) {
    if (key==27) {
        GLuint buffers[] = {
            triangleVBO, quadVBO
        };

        glDeleteBuffers(2, buffers);
        std::exit(0);
    }
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q13 - ESC Cleanup Two VBOs");
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffers();
    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);
    glutMainLoop();
    return 0;
}
