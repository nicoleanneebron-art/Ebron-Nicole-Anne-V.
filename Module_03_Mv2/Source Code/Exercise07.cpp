#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.07f, 0.11f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.35f, 0.90f, 0.75f);
    glLineWidth(3.0f);
    glPushMatrix();
    glTranslatef(-0.35f, -0.15f, 0.0f);
    glScalef(0.003f, 0.003f, 1.0f);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'I');
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 450);
    glutCreateWindow("Q07 - Stroke Font Practice");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
