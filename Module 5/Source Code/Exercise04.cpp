#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint shapeVBO;

void initBuffer() {
    GLfloat triangle[] = {
        0, .7f, -.7f, -.55f, .7f, -.55f
    };

    glGenBuffers(1, &shapeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void cleanup() {
    // Stops OpenGL from reading the vertex-array client state.
    glDisableClientState(GL_VERTEX_ARRAY);

    // Removes the current array-buffer binding.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Releases the GPU buffer owned by this program.
    glDeleteBuffers(1, &shapeVBO);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.3f, .85f, .6f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);

    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key==27) {
        cleanup();
        std::exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q04 - Full VBO Cleanup Checklist");

    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
