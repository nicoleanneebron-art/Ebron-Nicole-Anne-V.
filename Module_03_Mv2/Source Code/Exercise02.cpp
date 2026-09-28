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
    glClearColor(0.07f, 0.10f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(-0.45f, 0.45f);
    drawText(GLUT_BITMAP_HELVETICA_10, "Learning OpenGL");

    glRasterPos2f(-0.45f, 0.05f);
    drawText(GLUT_BITMAP_HELVETICA_18, "Learning OpenGL");

    glRasterPos2f(-0.45f, -0.40f);
    drawText(GLUT_BITMAP_TIMES_ROMAN_24, "Learning OpenGL");

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(650, 450);
    glutCreateWindow("Q02 - Font Size Comparison");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
