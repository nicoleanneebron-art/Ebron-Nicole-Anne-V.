#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <cstdio>

const float PI = 3.14159265f;
float markerX = 0.0f;
float markerY = 0.0f;
float hoverX = 0.0f;
float hoverY = 0.0f;
float markerSize = 0.11f;

void toGL(int x, int y, float* openGLX, float* openGLY) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    *openGLX = 2.0f * x / width - 1.0f;
    *openGLY = 1.0f - 2.0f * y / height;
}

void drawText(void* font, const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(font, *c);
}

void display() {
    glClearColor(0.05f, 0.09f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.30f, 0.84f, 0.75f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(markerX, markerY);
    for (int i = 0; i <= 40; ++i) {
        float angle = 2.0f * PI * i / 40.0f;
        glVertex2f(markerX + markerSize * std::cos(angle),
            markerY + markerSize * std::sin(angle));
    }
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(markerX - 0.09f, markerY + markerSize + 0.06f);
    drawText(GLUT_BITMAP_HELVETICA_18, "Marker");

    char readout[64];
    std::snprintf(readout, sizeof(readout), "Mouse: (%.2f, %.2f)", hoverX, hoverY);
    glColor3f(0.75f, 0.90f, 1.0f);
    glRasterPos2f(-0.95f, 0.90f);
    drawText(GLUT_BITMAP_HELVETICA_18, readout);

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        toGL(x, y, &markerX, &markerY);
        glutPostRedisplay();
    }
}

void passiveMotion(int x, int y) {
    toGL(x, y, &hoverX, &hoverY);
    glutPostRedisplay();
}

void idle() {
    float seconds = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    markerSize = 0.11f + 0.018f * std::sin(seconds * 3.0f);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 550);
    glutCreateWindow("Q20 - Interactive Text Placer");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passiveMotion);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
