#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>
GLuint textureId = 0;
float angle = 0.0f;

void createTexture() {
    unsigned char pixels[] = {
        230, 170, 80,   75, 35, 15,
        75, 35, 15,     230, 170, 80
    };
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
}

void cubeVertex(float s, float t, float nx, float ny, float nz, float x, float y, float z) {
    glNormal3f(nx, ny, nz);
    glTexCoord2f(s, t);
    glVertex3f(x, y, z);
}

void drawTexturedCube() {
    glBegin(GL_QUADS);
    cubeVertex(0, 0, 0, 0, 1, -1, -1, 1);
    cubeVertex(1, 0, 0, 0, 1, 1, -1, 1);
    cubeVertex(1, 1, 0, 0, 1, 1, 1, 1);
    cubeVertex(0, 1, 0, 0, 1, -1, 1, 1);
    cubeVertex(0, 0, 0, 0, -1, 1, -1, -1);
    cubeVertex(1, 0, 0, 0, -1, -1, -1, -1);
    cubeVertex(1, 1, 0, 0, -1, -1, 1, -1);
    cubeVertex(0, 1, 0, 0, -1, 1, 1, -1);
    cubeVertex(0, 0, -1, 0, 0, -1, -1, -1);
    cubeVertex(1, 0, -1, 0, 0, -1, -1, 1);
    cubeVertex(1, 1, -1, 0, 0, -1, 1, 1);
    cubeVertex(0, 1, -1, 0, 0, -1, 1, -1);
    cubeVertex(0, 0, 1, 0, 0, 1, -1, 1);
    cubeVertex(1, 0, 1, 0, 0, 1, -1, -1);
    cubeVertex(1, 1, 1, 0, 0, 1, 1, -1);
    cubeVertex(0, 1, 1, 0, 0, 1, 1, 1);
    cubeVertex(0, 0, 0, 1, 0, -1, 1, 1);
    cubeVertex(1, 0, 0, 1, 0, 1, 1, 1);
    cubeVertex(1, 1, 0, 1, 0, 1, 1, -1);
    cubeVertex(0, 1, 0, 1, 0, -1, 1, -1);
    cubeVertex(0, 0, 0, -1, 0, -1, -1, -1);
    cubeVertex(1, 0, 0, -1, 0, 1, -1, -1);
    cubeVertex(1, 1, 0, -1, 0, 1, -1, 1);
    cubeVertex(0, 1, 0, -1, 0, -1, -1, 1);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 2.5, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(angle, 1.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, textureId);
    drawTexturedCube();
    glutSwapBuffers();
}

void animate(int value) {
    angle += 0.8f;
    if (angle >= 360.0f) angle = 0.0f;
    glutPostRedisplay();
    glutTimerFunc(16, animate, value);
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) {
        glDeleteTextures(1, &textureId);
        std::exit(0);
    }
}

void reshape(int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, static_cast<double>(width) / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(900, 650);
    glutCreateWindow("Module 08 - Exercise15 - Textured Rotating Cube");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    createTexture();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, animate, 0);
    glutMainLoop();
    return 0;
}

