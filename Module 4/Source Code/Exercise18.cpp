#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int currentShape = 1;

GLfloat triangle[] = {0.0f,0.70f, -0.70f,-0.55f, 0.70f,-0.55f};
GLfloat quad[] = {-0.62f,-0.55f, 0.62f,-0.55f, 0.62f,0.55f, -0.62f,0.55f};
GLfloat pentagon[] = {
     0.00f,0.70f, -0.67f,0.22f, -0.42f,-0.57f,
     0.42f,-0.57f, 0.67f,0.22f
};

void display() {
    glClearColor(0.05f, 0.08f, 0.13f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.30f, 0.82f, 0.78f);
    glEnableClientState(GL_VERTEX_ARRAY);

    if (currentShape == 1) {
        glVertexPointer(2, GL_FLOAT, 0, triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    } else if (currentShape == 2) {
        glVertexPointer(2, GL_FLOAT, 0, quad);
        glDrawArrays(GL_QUADS, 0, 4);
    } else {
        glVertexPointer(2, GL_FLOAT, 0, pentagon);
        glDrawArrays(GL_POLYGON, 0, 5);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    if (key >= '1' && key <= '3') {
        currentShape = key - '0';
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(650, 520);
    glutCreateWindow("Q18 - Keyboard-Switched Vertex Arrays");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
