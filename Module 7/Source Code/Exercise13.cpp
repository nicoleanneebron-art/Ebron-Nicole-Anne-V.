#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint quadVBO = 0;
const GLsizeiptr POSITION_BYTES = 12 * sizeof(GLfloat);

void initializeBuffer() {
    GLfloat positions[] = {
        -0.7f, -0.6f, 0.0f,
         0.7f, -0.6f, 0.0f,
         0.7f,  0.6f, 0.0f,
        -0.7f,  0.6f, 0.0f
    };
    GLfloat colors[] = {
        0.20f, 0.70f, 0.95f,
        0.25f, 0.90f, 0.65f,
        0.65f, 0.55f, 0.95f,
        0.20f, 0.80f, 0.85f
    };
    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glVertexPointer(3, GL_FLOAT, 0, reinterpret_cast<void*>(0));
    glColorPointer(3, GL_FLOAT, 0, reinterpret_cast<void*>(POSITION_BYTES));
    glBegin(GL_QUADS);
    for (int index = 0; index < 4; ++index) {
        glArrayElement(index);
    }
    glEnd();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) {
        glDeleteBuffers(1, &quadVBO);
        std::exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 550);
    glutCreateWindow("Q13 - Static Color VBO Quad");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    initializeBuffer();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
