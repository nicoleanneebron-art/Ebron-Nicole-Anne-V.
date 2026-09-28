#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdio>

int mousePixelX = 0;
int mousePixelY = 0;

void drawText(const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void display() {
    glClearColor(0.08f, 0.12f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    char message[64];
    std::snprintf(message, sizeof(message), "Mouse at (%d, %d)", mousePixelX, mousePixelY);
    glColor3f(0.85f, 0.95f, 1.0f);
    glRasterPos2f(-0.32f, 0.0f);
    drawText(message);

    glFlush();
}

void passiveMotion(int x, int y) {
    mousePixelX = x;
    mousePixelY = y;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q10 - Passive Motion Pixel Readout");
    glutDisplayFunc(display);
    glutPassiveMotionFunc(passiveMotion);
    glutMainLoop();
    return 0;
}
