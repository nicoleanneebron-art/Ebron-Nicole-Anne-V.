#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const int PETAL_COUNT = 12;
const int DISC_SEGMENTS = 40;
const float PI = 3.14159265f;
GLfloat petalVertices[PETAL_COUNT * 3 * 2];
GLfloat petalColors[PETAL_COUNT * 3 * 3];
GLfloat discVertices[(DISC_SEGMENTS + 1) * 2];
GLubyte discIndices[DISC_SEGMENTS + 2];

void buildFlower() {
    const float centerY = 0.23f;
    for (int i = 0; i < PETAL_COUNT; ++i) {
        float angle = 2.0f * PI * i / PETAL_COUNT;
        float spread = PI / PETAL_COUNT * 0.72f;
        int vertex = i * 6;
        petalVertices[vertex] = 0.0f;
        petalVertices[vertex + 1] = centerY;
        petalVertices[vertex + 2] = 0.62f * std::cos(angle - spread);
        petalVertices[vertex + 3] = centerY + 0.62f * std::sin(angle - spread);
        petalVertices[vertex + 4] = 0.62f * std::cos(angle + spread);
        petalVertices[vertex + 5] = centerY + 0.62f * std::sin(angle + spread);

        float r = 0.35f + 0.55f * ((i % 3) == 0);
        float g = 0.45f + 0.40f * ((i % 3) == 1);
        float b = 0.45f + 0.45f * ((i % 3) == 2);
        for (int j = 0; j < 3; ++j) {
            int color = (i * 3 + j) * 3;
            petalColors[color] = r;
            petalColors[color + 1] = g;
            petalColors[color + 2] = b;
        }
    }

    discVertices[0] = 0.0f;
    discVertices[1] = centerY;
    discIndices[0] = 0;
    for (int i = 0; i < DISC_SEGMENTS; ++i) {
        float angle = 2.0f * PI * i / DISC_SEGMENTS;
        discVertices[(i + 1) * 2] = 0.22f * std::cos(angle);
        discVertices[(i + 1) * 2 + 1] = centerY + 0.22f * std::sin(angle);
        discIndices[i + 1] = static_cast<GLubyte>(i + 1);
    }
    discIndices[DISC_SEGMENTS + 1] = 1;
}

void display() {
    glClearColor(0.55f, 0.80f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat ground[] = {-1.0f,-1.0f, 1.0f,-1.0f, 1.0f,-0.62f, -1.0f,-0.62f};
    GLfloat stem[] = {-0.045f,-0.70f, 0.045f,-0.70f, 0.045f,0.23f, -0.045f,0.23f};

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(0.25f, 0.65f, 0.32f);
    glVertexPointer(2, GL_FLOAT, 0, ground);
    glDrawArrays(GL_QUADS, 0, 4);
    glColor3f(0.16f, 0.52f, 0.25f);
    glVertexPointer(2, GL_FLOAT, 0, stem);
    glDrawArrays(GL_QUADS, 0, 4);

    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, petalVertices);
    glColorPointer(3, GL_FLOAT, 0, petalColors);
    glDrawArrays(GL_TRIANGLES, 0, PETAL_COUNT * 3);
    glDisableClientState(GL_COLOR_ARRAY);

    glColor3f(1.0f, 0.78f, 0.18f);
    glVertexPointer(2, GL_FLOAT, 0, discVertices);
    glDrawElements(GL_TRIANGLE_FAN, DISC_SEGMENTS + 2, GL_UNSIGNED_BYTE, discIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 600);
    glutCreateWindow("Q20 - Procedural Flower Scene");
    buildFlower();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
