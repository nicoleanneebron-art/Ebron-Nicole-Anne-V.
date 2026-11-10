#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint pyramidVBO = 0;
float angle = 0.0f;
const int VERTEX_COUNT = 12;
const GLsizeiptr POSITION_BYTES = VERTEX_COUNT * 3 * sizeof(GLfloat);

void initializePyramid() {
    GLfloat positions[] = {
         0.0f,  1.0f,  0.0f, -0.9f, -0.8f,  0.9f,  0.9f, -0.8f,  0.9f,
         0.0f,  1.0f,  0.0f,  0.9f, -0.8f,  0.9f,  0.0f, -0.8f, -0.9f,
         0.0f,  1.0f,  0.0f,  0.0f, -0.8f, -0.9f, -0.9f, -0.8f,  0.9f,
        -0.9f, -0.8f,  0.9f,  0.0f, -0.8f, -0.9f,  0.9f, -0.8f,  0.9f
    };
    GLfloat colors[] = {
        0.95f, 0.35f, 0.35f, 0.95f, 0.35f, 0.35f, 0.95f, 0.35f, 0.35f,
        0.25f, 0.75f, 0.95f, 0.25f, 0.75f, 0.95f, 0.25f, 0.75f, 0.95f,
        0.35f, 0.90f, 0.60f, 0.35f, 0.90f, 0.60f, 0.35f, 0.90f, 0.60f,
        0.75f, 0.55f, 0.95f, 0.75f, 0.55f, 0.95f, 0.75f, 0.55f, 0.95f
    };
    glGenBuffers(1, &pyramidVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -4.0f);
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
    glVertexPointer(3, GL_FLOAT, 0, reinterpret_cast<void*>(0));
    glColorPointer(3, GL_FLOAT, 0, reinterpret_cast<void*>(POSITION_BYTES));
    glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}

void animate(int value) {
    angle += 1.0f;
    if (angle >= 360.0f) {
        angle = 0.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, animate, value);
}

void monitorKeyboard(unsigned char key, int, int) {
    if (key == 27) {
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &pyramidVBO);
        std::exit(0);
    }
}

void reshape(int width, int height) {
    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, static_cast<double>(width) / height, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 600);
    glutCreateWindow("Q15 - X-Axis Color Pyramid");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    initializePyramid();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(monitorKeyboard);
    glutTimerFunc(16, animate, 0);
    glutMainLoop();
    return 0;
}
