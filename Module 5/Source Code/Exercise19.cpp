#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint positionVBO, colorVBO;
int scheme=0;

const GLfloat palettes[3][12]={
    {
        .2f, .7f, 1, .3f, .9f, .55f, .95f, .7f, .25f, .7f, .4f, .9f
    }
    ,
    {
        .95f, .35f, .35f, 1, .65f, .2f, .95f, .9f, .25f, .85f, .35f, .65f
    }
    ,
    {
        .35f, .9f, .85f, .25f, .65f, .95f, .45f, .9f, .55f, .65f, .45f, .95f
    }
};

void initBuffers() {
    GLfloat p[] = {
        -.6f, -.55f, .6f, -.55f, .6f, .55f, -.6f, .55f
    };

    glGenBuffers(1, &positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), p, GL_STATIC_DRAW);
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(palettes[0]), palettes[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glColorPointer(3, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_QUADS, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key=='c'||key=='C') {
        scheme=(scheme+1)%3;
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        GLfloat* p=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        if (p) {
            for (int i=0;i<12;i++)p[i]=palettes[scheme][i];
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glutPostRedisplay();
    }
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q19 - Keyboard Color Change via glMapBuffer");
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.06f, .09f, .14f, 1);
    initBuffers();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
