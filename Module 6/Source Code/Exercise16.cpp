#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

bool cullingOn=false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (cullingOn)glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glBegin(GL_TRIANGLES);

    glColor3f(.25f, .75f, .95f);
    glVertex2f(-.85f, -.45f);
    glVertex2f(-.15f, -.45f);
    glVertex2f(-.5f, .45f);

    glColor3f(.35f, .9f, .55f);
    glVertex2f(.15f, -.45f);
    glVertex2f(.5f, .45f);
    glVertex2f(.85f, -.45f);

    glEnd();
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key=='f'||key=='F') {
        cullingOn=!cullingOn;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q16 - Toggleable Face Culling");

#ifndef __APPLE__
    if (glewInit()!=GLEW_OK)return 1;

#endif
    glClearColor(.06f, .09f, .14f, 1);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
