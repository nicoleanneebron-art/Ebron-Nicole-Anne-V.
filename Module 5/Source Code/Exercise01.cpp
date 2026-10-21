#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint pointVBO = 0;

void initBuffer() {
    GLfloat points[] = {
        -0.55f, 0.55f, 0.55f, 0.55f, 0.0f, 0.0f,
        -0.55f, -0.55f, 0.55f, -0.55f
    };

    glGenBuffers(1, &pointVBO);

    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.3f, 0.85f, 0.75f);

    glPointSize(12.0f);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);

    glVertexPointer(2, GL_FLOAT, 0, (void*)0);

    glDrawArrays(GL_POINTS, 0, 5);

    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) {
        glDeleteBuffers(1, &pointVBO);

        std::exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);

    glutCreateWindow("Q01 - VBO X-Pattern Points");

    if (glewInit() != GLEW_OK) return 1;

    glClearColor(0.06f, 0.09f, 0.14f, 1.0f);

    initBuffer();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
