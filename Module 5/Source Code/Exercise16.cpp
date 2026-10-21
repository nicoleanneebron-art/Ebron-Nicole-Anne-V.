#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <cmath>

const int SEGMENTS=40;
const float PI=3.14159265f;

GLuint sunVBO, groundVBO, groundEBO, trunkVBO, canopyVBO;

void upload(GLuint& id, const GLfloat* p, int bytes) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, bytes, p, GL_STATIC_DRAW);
}

void initScene() {
    GLfloat sun[(SEGMENTS+2)*2];
    sun[0]=-.65f;
    sun[1]=.62f;
    for (int i=0;i<=SEGMENTS;i++) {
        float a=2*PI*i/SEGMENTS;
        sun[(i+1)*2]=-.65f+.17f*cosf(a);
        sun[(i+1)*2+1]=.62f+.17f*sinf(a);
    }
    upload(sunVBO, sun, sizeof(sun));

    GLfloat ground[] = {
        -1, -1, 1, -1, 1, -.45f, -1, -.45f
    };

    upload(groundVBO, ground, sizeof(ground));
    GLubyte idx[] = {
        0, 1, 2, 0, 2, 3
    };

    glGenBuffers(1, &groundEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

    GLfloat trunk[] = {
        .48f, -.45f, .62f, -.45f, .62f, .18f, .48f, .18f
    };

    upload(trunkVBO, trunk, sizeof(trunk));
    GLfloat canopy[] = {
        .55f, .72f, .18f, .08f, .92f, .08f
    };

    upload(canopyVBO, canopy, sizeof(canopy));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawArrays(GLuint id, GLenum mode, int count, float r, float g, float b) {
    glColor3f(r, g, b);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glDrawArrays(mode, 0, count);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    drawArrays(sunVBO, GL_TRIANGLE_FAN, SEGMENTS+2, 1, .8f, .2f);

    glColor3f(.25f, .65f, .32f);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundEBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    drawArrays(trunkVBO, GL_QUADS, 4, .42f, .24f, .12f);
    drawArrays(canopyVBO, GL_TRIANGLES, 3, .15f, .55f, .25f);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitWindowSize(750, 550);
    glutCreateWindow("Q16 - Three-Shape VBO Scene");
    if (glewInit() != GLEW_OK) {
        return 1;
    }
    glClearColor(.5f, .78f, .92f, 1);
    initScene();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
