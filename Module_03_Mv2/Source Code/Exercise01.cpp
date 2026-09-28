#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void drawText(void* font, const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(font, *c);
}

void display() {
    glClearColor(0.08f, 0.12f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.22f, 0.0f);
    drawText(GLUT_BITMAP_HELVETICA_18, "Nicole Anne V. Ebron");

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 350);
    glutCreateWindow("Q01 - Display Your Name");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
