#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>
#if __has_include("stb_image.h")
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define HAS_STB_IMAGE 1
#else
#define HAS_STB_IMAGE 0
#endif

GLuint textureId = 0;
float angle = 0.0f;

void uploadFallbackWood() {
    unsigned char wood[] = {
        155, 82, 35,   205, 135, 65,
        95, 45, 20,    175, 95, 40
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, wood);
}

void loadWoodTexture() {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#if HAS_STB_IMAGE
    int width = 0;
    int height = 0;
    int channels = 0;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load("woodtexture.jpg", &width, &height, &channels, 0);
    if (data) {
        GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
        std::cout << "Loaded woodtexture.jpg successfully.\n";
        return;
    }
    std::cerr << "woodtexture.jpg could not be loaded; using fallback wood texture.\n";
#else
    std::cerr << "stb_image.h was not found; using fallback wood texture.\n";
#endif
    uploadFallbackWood();
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
    glutCreateWindow("Module 08 - Exercise16 - Wood-Textured Object");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    loadWoodTexture();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, animate, 0);
    glutMainLoop();
    return 0;
}

