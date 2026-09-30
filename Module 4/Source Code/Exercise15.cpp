#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const int SUN_SEGMENTS = 40;
const float PI = 3.14159265f;
GLfloat sun[(SUN_SEGMENTS + 1) * 2];
GLubyte sunIndices[SUN_SEGMENTS + 2];

void buildSun() {
    sun[0] = 0.62f; sun[1] = 0.58f;
    sunIndices[0] = 0;
    for (int i = 0; i < SUN_SEGMENTS; ++i) {
        float angle = 2.0f * PI * i / SUN_SEGMENTS;
        sun[(i + 1) * 2] = 0.62f + 0.18f * std::cos(angle);
        sun[(i + 1) * 2 + 1] = 0.58f + 0.18f * std::sin(angle);
        sunIndices[i + 1] = static_cast<GLubyte>(i + 1);
    }
    sunIndices[SUN_SEGMENTS + 1] = 1;
}

void drawArray(GLenum mode, GLfloat* vertices, int count) {
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawArrays(mode, 0, count);
}

void display() {
    glClearColor(0.50f, 0.78f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat ground[] = {-1.0f,-1.0f, 1.0f,-1.0f, 1.0f,-0.42f, -1.0f,-0.42f};
    GLfloat mountain[] = {-0.95f,-0.42f, -0.25f,0.50f, 0.30f,-0.42f};
    GLfloat mountainTwo[] = {-0.30f,-0.42f, 0.30f,0.30f, 0.90f,-0.42f};

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(0.25f, 0.65f, 0.32f);
    drawArray(GL_QUADS, ground, 4);
    glColor3f(0.27f, 0.38f, 0.43f);
    drawArray(GL_TRIANGLES, mountain, 3);
    glColor3f(0.34f, 0.47f, 0.46f);
    drawArray(GL_TRIANGLES, mountainTwo, 3);
    glColor3f(1.0f, 0.82f, 0.25f);
    glVertexPointer(2, GL_FLOAT, 0, sun);
    glDrawElements(GL_TRIANGLE_FAN, SUN_SEGMENTS + 2, GL_UNSIGNED_BYTE, sunIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(750, 550);
    glutCreateWindow("Q15 - Fully Array-Based Scene");
    buildSun();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
