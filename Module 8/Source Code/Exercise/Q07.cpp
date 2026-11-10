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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.25f, 0.75f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(-0.6f, -0.4f);
    glVertex2f(0.6f, -0.4f);
    glVertex2f(0.6f, 0.4f);
    glVertex2f(-0.6f, 0.4f);
    glEnd();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) {
        glDeleteTextures(1, &textureId);
        std::cout << "Texture deleted.\n";
        std::exit(0);
    }
}

void reshape2D(int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 08 - Exercise07 - Generate Texture ID");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    std::cout << "Generated texture ID: " << textureId << '\n';
    glutDisplayFunc(display);
    glutReshapeFunc(reshape2D);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

