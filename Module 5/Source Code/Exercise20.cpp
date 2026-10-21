#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint shipPositionVBO, shipColorVBO, groundPositionVBO, groundIndexVBO;
float shipOffset=0, direction=1;

void initBuffers() {
    GLfloat ship[] = {
        -.12f, .15f, -.3f, -.15f, .3f, -.15f
    };

    GLfloat colors[] = {
        .2f, .75f, 1, .3f, .9f, .6f, .95f, .7f, .25f
    };

    GLfloat ground[] = {
        -1, -1, 1, -1, 1, -.55f, -1, -.55f
    };

    GLubyte index[] = {
        0, 1, 2, 0, 2, 3
    };

    glGenBuffers(1, &shipPositionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, shipPositionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ship), ship, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &shipColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, shipColorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glGenBuffers(1, &groundPositionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, groundPositionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ground), ground, GL_STATIC_DRAW);

    glGenBuffers(1, &groundIndexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(.2f, .55f, .3f);
    glBindBuffer(GL_ARRAY_BUFFER, groundPositionVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, shipPositionVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, shipColorVBO);
    glColorPointer(3, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}

void timer(int) {
    float step=.18f*direction;
    shipOffset+=step;
    if (shipOffset>.65f||shipOffset<-.65f) {
        direction=-direction;
        step=-step;
        shipOffset+=2*step;
    }
    glBindBuffer(GL_ARRAY_BUFFER, shipPositionVBO);
    GLfloat* p=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if (p) {
        for (int i=0;i<3;i++)p[i*2]+=step;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

void keyboard(unsigned char key, int, int) {
    if (key==27) {
        GLuint buffers[] = {
            shipPositionVBO, shipColorVBO, groundPositionVBO, groundIndexVBO
        };

        glDeleteBuffers(4, buffers);
        std::exit(0);
    }
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(800, 550);
    glutCreateWindow("Q20 - Animated Ship Over Indexed Ground");
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.45f, .75f, .92f, 1);
    initBuffers();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
