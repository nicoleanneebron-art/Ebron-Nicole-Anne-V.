#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

float baseAngle = 20.0f;
float jointAngle = 35.0f;

void drawSegment(float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, -0.12f);
    glVertex2f(0.9f, -0.12f);
    glVertex2f(0.9f, 0.12f);
    glVertex2f(0.0f, 0.12f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-0.75f, -0.25f, 0.0f);
    glPushMatrix();
    glRotatef(baseAngle, 0.0f, 0.0f, 1.0f);
    drawSegment(0.25f, 0.8f, 0.95f);
    glTranslatef(0.9f, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(jointAngle, 0.0f, 0.0f, 1.0f);
    drawSegment(0.35f, 0.9f, 0.6f);
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 'a':
            baseAngle += 5.0f;
            break;
        case 'A':
            baseAngle -= 5.0f;
            break;
        case 's':
            jointAngle += 5.0f;
            break;
        case 'S':
            jointAngle -= 5.0f;
            break;
        case 27:
            std::exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(850, 600);
    glutCreateWindow("Q18 - Keyboard-Controlled Two-Joint Arm");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif
    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
