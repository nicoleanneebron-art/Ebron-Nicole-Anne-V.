#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const int SEGMENTS = 80;
const float PI = 3.14159265f;
GLfloat vertices[(SEGMENTS + 2) * 2];
GLfloat colors[(SEGMENTS + 2) * 3];

void buildCircle() {
    vertices[0] = 0.0f; vertices[1] = 0.0f;
    colors[0] = 1.0f; colors[1] = 1.0f; colors[2] = 1.0f;

    for (int i = 0; i <= SEGMENTS; ++i) {
        float t = static_cast<float>(i) / SEGMENTS;
        float angle = 2.0f * PI * t;
        int vertex = i + 1;
        vertices[vertex * 2] = 0.72f * std::cos(angle);
        vertices[vertex * 2 + 1] = 0.72f * std::sin(angle);
        colors[vertex * 3] = 0.25f + 0.65f * t;
        colors[vertex * 3 + 1] = 0.85f - 0.55f * t;
        colors[vertex * 3 + 2] = 0.90f;
    }
}

void display() {
    glClearColor(0.05f, 0.08f, 0.13f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLE_FAN, 0, SEGMENTS + 2);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q11 - Procedural Shaded Circle");
    buildCircle();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
