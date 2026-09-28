#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdio>

int score = 0;
float shapeColor[3] = {0.25f, 0.75f, 0.90f};

const float milestoneColors[6][3] = {
    {0.25f, 0.75f, 0.90f},
    {0.30f, 0.85f, 0.55f},
    {0.95f, 0.75f, 0.25f},
    {0.90f, 0.40f, 0.45f},
    {0.65f, 0.45f, 0.90f},
    {0.25f, 0.85f, 0.80f}
};

void drawText(const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void display() {
    glClearColor(0.05f, 0.09f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3fv(shapeColor);
    glBegin(GL_QUADS);
    glVertex2f(-0.38f, -0.38f);
    glVertex2f(0.38f, -0.38f);
    glVertex2f(0.38f, 0.38f);
    glVertex2f(-0.38f, 0.38f);
    glEnd();

    char message[40];
    std::snprintf(message, sizeof(message), "Score: %d", score);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.13f, 0.0f);
    drawText(message);
    glFlush();
}

void mouse(int button, int state, int, int) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        ++score;
        int colorStage = (score / 5) % 6;
        shapeColor[0] = milestoneColors[colorStage][0];
        shapeColor[1] = milestoneColors[colorStage][1];
        shapeColor[2] = milestoneColors[colorStage][2];
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(650, 500);
    glutCreateWindow("Q19 - HUD Score with Color Milestones");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
