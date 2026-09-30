#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.05f, 0.08f, 0.13f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // glDrawArrays: 12 floats storing 6 vertices, including 2 duplicates.
    GLfloat arrayQuad[] = {
        -0.88f,-0.48f, -0.12f,-0.48f, -0.12f,0.48f,
        -0.88f,-0.48f, -0.12f, 0.48f, -0.88f,0.48f
    };

    // glDrawElements: 8 floats storing 4 unique vertices + 6 indices.
    GLfloat indexedQuad[] = {
         0.12f,-0.48f, 0.88f,-0.48f,
         0.88f, 0.48f, 0.12f, 0.48f
    };
    GLubyte indices[] = {0,1,2, 0,2,3};

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(0.25f, 0.72f, 0.95f);
    glVertexPointer(2, GL_FLOAT, 0, arrayQuad);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glColor3f(0.30f, 0.88f, 0.55f);
    glVertexPointer(2, GL_FLOAT, 0, indexedQuad);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(750, 450);
    glutCreateWindow("Q16 - glDrawArrays vs glDrawElements");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
