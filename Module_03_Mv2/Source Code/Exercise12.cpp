#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float labelX = -0.9f;
float speed = 0.55f;
int previousTime = 0;

void drawText(const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void display() {
    glClearColor(0.06f, 0.10f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.35f, 0.90f, 0.75f);
    glRasterPos2f(labelX, 0.0f);
    drawText("Bouncing Label");
    glutSwapBuffers();
}

void idle() {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float seconds = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;
    labelX += speed * seconds;

    if (labelX >= 0.62f) {
        labelX = 0.62f;
        speed = -speed;
    } else if (labelX <= -0.9f) {
        labelX = -0.9f;
        speed = -speed;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 420);
    glutCreateWindow("Q12 - Idle-Driven Bouncing Label");
    previousTime = glutGet(GLUT_ELAPSED_TIME);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
