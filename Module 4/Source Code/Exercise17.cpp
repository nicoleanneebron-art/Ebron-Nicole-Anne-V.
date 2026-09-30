#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const int TEETH = 16;
const float PI = 3.14159265f;
GLfloat gearVertices[(TEETH + 2) * 2];
GLubyte evenTriangles[(TEETH / 2) * 3];
GLubyte oddTriangles[(TEETH / 2) * 3];

void buildGear() {
    gearVertices[0] = 0.0f;
    gearVertices[1] = 0.0f;

    for (int i = 0; i <= TEETH; ++i) {
        int point = i % TEETH;
        float angle = 2.0f * PI * point / TEETH;
        float radius = (point % 2 == 0) ? 0.78f : 0.58f;
        gearVertices[(i + 1) * 2] = radius * std::cos(angle);
        gearVertices[(i + 1) * 2 + 1] = radius * std::sin(angle);
    }

    int even = 0;
    int odd = 0;
    for (int i = 0; i < TEETH; ++i) {
        GLubyte* target = (i % 2 == 0) ? evenTriangles : oddTriangles;
        int& position = (i % 2 == 0) ? even : odd;
        target[position++] = 0;
        target[position++] = static_cast<GLubyte>(i + 1);
        target[position++] = static_cast<GLubyte>(i + 2);
    }
}

void display() {
    glClearColor(0.05f, 0.08f, 0.13f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, gearVertices);

    glColor3f(0.20f, 0.72f, 0.95f);
    glDrawElements(GL_TRIANGLES, (TEETH / 2) * 3, GL_UNSIGNED_BYTE, evenTriangles);
    glColor3f(0.30f, 0.88f, 0.58f);
    glDrawElements(GL_TRIANGLES, (TEETH / 2) * 3, GL_UNSIGNED_BYTE, oddTriangles);

    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q17 - Procedural Gear Shape");
    buildGear();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
