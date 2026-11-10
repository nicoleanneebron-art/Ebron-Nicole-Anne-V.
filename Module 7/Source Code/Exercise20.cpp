#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>

GLuint baseVBO = 0;
float armAngle = 0.0f;
const GLsizeiptr POSITION_BYTES = 12 * sizeof(GLfloat);

#ifndef __APPLE__
void APIENTRY debugCallback(GLenum, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*) {
    std::cerr << "OpenGL debug message - type " << type
              << ", severity " << severity << ": " << message << '\n';
}
#endif

void initializeBase() {
    GLfloat positions[] = {
        -1.4f, -1.2f, 0.0f,
         1.4f, -1.2f, 0.0f,
         1.4f, -0.8f, 0.0f,
        -1.4f, -0.8f, 0.0f
    };
    GLfloat colors[] = {
        0.15f, 0.55f, 0.85f,
        0.20f, 0.75f, 0.85f,
        0.30f, 0.90f, 0.60f,
        0.20f, 0.65f, 0.75f
    };
    glGenBuffers(1, &baseVBO);
    glBindBuffer(GL_ARRAY_BUFFER, baseVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawVBOBase() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, baseVBO);
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
}

void drawSegment(float length, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex3f(-0.12f, 0.0f, 0.0f);
    glVertex3f(0.12f, 0.0f, 0.0f);
    glVertex3f(0.12f, length, 0.0f);
    glVertex3f(-0.12f, length, 0.0f);
    glEnd();
}

void drawArm() {
    glPushMatrix();
    glTranslatef(0.0f, -0.8f, 0.05f);
    glRotatef(armAngle, 0.0f, 0.0f, 1.0f);
    drawSegment(1.2f, 0.30f, 0.85f, 0.65f);
    glTranslatef(0.0f, 1.2f, 0.0f);
    glPushMatrix();
    glRotatef(-armAngle * 1.5f, 0.0f, 0.0f, 1.0f);
    drawSegment(0.9f, 0.35f, 0.70f, 0.95f);
    glPopMatrix();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.5, 5.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawVBOBase();
    drawArm();
    glutSwapBuffers();
}

void animateArm(int value) {
    armAngle += 1.0f;
    if (armAngle >= 360.0f) {
        armAngle = 0.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, animateArm, value);
}

void cleanupAndExit(unsigned char key, int, int) {
    if (key == 27) {
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &baseVBO);
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
    gluPerspective(50.0, static_cast<double>(width) / height, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(850, 650);
    glutCreateWindow("Q20 - VBO Base and Hierarchical Arm");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    if (GLEW_VERSION_4_3 || GLEW_KHR_debug) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugCallback, nullptr);
    }
#endif
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    initializeBase();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(cleanupAndExit);
    glutTimerFunc(16, animateArm, 0);
    glutMainLoop();
    return 0;
}
