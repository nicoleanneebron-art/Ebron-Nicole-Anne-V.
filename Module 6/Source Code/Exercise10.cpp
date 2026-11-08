#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint triangleVBO = 0;

void multiply4x4(const float* a, const float* b, float* result) {
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result[col * 4 + row] = 0.0f;

            for (int k = 0; k < 4; ++k)
            result[col * 4 + row] += a[k * 4 + row] * b[col * 4 + k];
        }
    }
}

void applyMatrix(float* v, const float* m) {
    float x=v[0], y=v[1], z=v[2], w=1.0f;

    v[0]=m[0]*x+m[4]*y+m[8]*z+m[12]*w;

    v[1]=m[1]*x+m[5]*y+m[9]*z+m[13]*w;

    v[2]=m[2]*x+m[6]*y+m[10]*z+m[14]*w;
}

void initBuffer() {
    GLfloat triangle[] = {
        0, .45f, 0, -.4f, -.35f, 0, .4f, -.35f, 0
    };

    float translate[16] = {
        1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, .3f, .2f, 0, 1
    };

    float scale[16] = {
        1.4f, 0, 0, 0, 0, 1.4f, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
    };

    float combined[16];

    multiply4x4(translate, scale, combined);

    for (int i=0;i<9;i+=3) applyMatrix(&triangle[i], combined);

    glGenBuffers(1, &triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.3f, .78f, .9f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q10 - Combined Translate and Scale");

#ifndef __APPLE__
    if (glewInit()!=GLEW_OK)return 1;

#endif
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
