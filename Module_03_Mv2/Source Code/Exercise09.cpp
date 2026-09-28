#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdio>

float mouseX = 0.0f;
float mouseY = 0.0f;

void drawText(const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void display() {
    glClearColor(0.08f, 0.12f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    char message[80];
    std::snprintf(message, sizeof(message), "OpenGL position: (%.2f, %.2f)", mouseX, mouseY);
    glColor3f(0.80f, 0.95f, 1.0f);
    glRasterPos2f(-0.48f, 0.0f);
    drawText(message);

    glFlush();
}

void motion(int x, int y) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    mouseX = 2.0f * x / width - 1.0f;
    mouseY = 1.0f - 2.0f * y / height;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q09 - Active Motion Coordinate Display");
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}
