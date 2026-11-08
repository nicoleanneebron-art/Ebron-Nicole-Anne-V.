#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <cmath>
#include <iostream>

const float PI=3.14159265f;

void rotateZ(float* v, float degrees) {
    float a=degrees*PI/180.0f;

    float m[16]={
        cosf(a), sinf(a), 0, 0, -sinf(a), cosf(a), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
    };

    float x=v[0], y=v[1], z=v[2], w=v[3];

    v[0]=m[0]*x+m[4]*y+m[8]*z+m[12]*w;

    v[1]=m[1]*x+m[5]*y+m[9]*z+m[13]*w;

    v[2]=m[2]*x+m[6]*y+m[10]*z+m[14]*w;

    v[3]=m[3]*x+m[7]*y+m[11]*z+m[15]*w;
}

void testRotation() {
    float position[4]={
        1, 0, 0, 1
    };

    float direction[4]={
        1, 0, 0, 0
    };

    rotateZ(position, 90);
    rotateZ(direction, 90);

    // Rotation acts on x/y directly, so both w=1 positions and w=0 directions rotate.
    // Translation instead depends on the last column multiplied by w, so w=0 ignores it.
    std::cout<<"Position: ("<<position[0]<<", "<<position[1]<<", w="<<position[3]<<")\n";

    std::cout<<"Direction: ("<<direction[0]<<", "<<direction[1]<<", w="<<direction[3]<<")\n";
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.3f, .85f, .7f);
    glLineWidth(5);

    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, .75f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Q13 - Rotation and Homogeneous Coordinates");

#ifndef __APPLE__
    if (glewInit()!=GLEW_OK)return 1;

#endif
    glClearColor(.06f, .09f, .14f, 1);
    testRotation();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
