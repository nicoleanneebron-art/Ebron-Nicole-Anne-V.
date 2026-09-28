#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void drawText(const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void display() {
    glClearColor(0.06f, 0.10f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.25f, 0.75f, 0.85f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.65f);
    glVertex2f(-0.55f, -0.25f);
    glVertex2f(0.55f, -0.25f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.25f, -0.55f);
    drawText("A filled triangle");

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q06 - Shape with Caption");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
