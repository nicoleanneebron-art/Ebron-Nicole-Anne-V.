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

void drawFloor() {
    glNormal3f(0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-5, -1.5f, 4);
    glTexCoord2f(4, 0); glVertex3f(5, -1.5f, 4);
    glTexCoord2f(4, 4); glVertex3f(5, -1.5f, -5);
    glTexCoord2f(0, 4); glVertex3f(-5, -1.5f, -5);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5.0, 4.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    GLfloat point[] = {3.0f, 4.0f, 4.0f, 1.0f};
    GLfloat direction[] = {-1.0f, 1.0f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, point);
    glLightfv(GL_LIGHT1, GL_POSITION, direction);
    glBindTexture(GL_TEXTURE_2D, textureId);
    drawFloor();
    glPushMatrix();
    glTranslatef(-1.5f, -0.5f, 0.0f);
    glScalef(0.9f, 0.9f, 0.9f);
    drawTexturedCube();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5f, -0.2f, -1.0f);
    glRotatef(35.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.75f, 1.25f, 0.75f);
    drawTexturedCube();
    glPopMatrix();
    glutSwapBuffers();
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
    glutCreateWindow("Module 08 - Exercise20 - Mini-Scene Integration");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.05f, 0.08f, 0.12f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    GLfloat pointColor[] = {1.0f, 0.75f, 0.45f, 1.0f};
    GLfloat directionColor[] = {0.35f, 0.55f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, pointColor);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, directionColor);
    createTexture();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

