#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint quadVBO;
float offset=0.0f, direction=1.0f;

void initBuffer() {
    GLfloat q[] = {
        -.35f, -.25f, .35f, -.25f, .35f, .25f, -.35f, .25f
    };

    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(q), q, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.3f, .82f, .72f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_QUADS, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}

void timer(int) {
    float step=.025f*direction;
    offset+=step;
    if (offset>.65f||offset<-.65f) {
        direction=-direction;
        step=-step;
        offset+=2*step;
    }

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    GLfloat* p=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    if (p) {
        for (int i=0;i<4;i++)p[i*2+1]+=step;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q15 - Bouncing glMapBuffer Animation");
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffer();
    glutDisplayFunc(display);
    glutTimerFunc(30, timer, 0);
    glutMainLoop();
    return 0;
}
