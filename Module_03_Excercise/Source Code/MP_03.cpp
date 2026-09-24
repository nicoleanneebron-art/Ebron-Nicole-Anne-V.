#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

// =========================
// CONSTANTS
// =========================

const int MAX_BURSTS = 20;
const int STAR_COUNT = 100;

const float PI = 3.14159265f;


// =========================
// BURST STRUCTURE
// =========================

struct Burst
{
    bool active;

    int type;

    float x;
    float y;

    float size;
    float brightness;

    float r;
    float g;
    float b;
};


// =========================
// GLOBAL VARIABLES
// =========================

Burst bursts[MAX_BURSTS];

float starX[STAR_COUNT];
float starY[STAR_COUNT];


// =========================
// DRAW TEXT
// =========================

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);

    for (char c : text)
    {
        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_12,
            c
        );
    }
}


// =========================
// DRAW STARS
// =========================

void drawStars()
{
    glPointSize(2.0f);

    glBegin(GL_POINTS);

    for (int i = 0; i < STAR_COUNT; i++)
    {
        // Slightly different brightness
        float brightness =
            0.35f + (i % 5) * 0.12f;

        glColor3f(
            brightness,
            brightness,
            brightness
        );

        glVertex2f(
            starX[i],
            starY[i]
        );
    }

    glEnd();
}


// =========================
// DRAW NIGHT SKY GROUND
// =========================

void drawGround()
{
    glColor3f(
        0.02f,
        0.025f,
        0.05f
    );

    glBegin(GL_QUADS);

    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.82f);
    glVertex2f(-1.0f, -0.82f);

    glEnd();

    // Small building silhouettes
    glColor3f(
        0.015f,
        0.018f,
        0.035f
    );

    glBegin(GL_QUADS);

    // Building 1
    glVertex2f(-0.95f, -0.82f);
    glVertex2f(-0.78f, -0.82f);
    glVertex2f(-0.78f, -0.55f);
    glVertex2f(-0.95f, -0.55f);

    // Building 2
    glVertex2f(-0.72f, -0.82f);
    glVertex2f(-0.52f, -0.82f);
    glVertex2f(-0.52f, -0.65f);
    glVertex2f(-0.72f, -0.65f);

    // Building 3
    glVertex2f(0.65f, -0.82f);
    glVertex2f(0.83f, -0.82f);
    glVertex2f(0.83f, -0.58f);
    glVertex2f(0.65f, -0.58f);

    // Building 4
    glVertex2f(0.84f, -0.82f);
    glVertex2f(0.98f, -0.82f);
    glVertex2f(0.98f, -0.68f);
    glVertex2f(0.84f, -0.68f);

    glEnd();
}


// =========================
// DRAW FIREWORK BURST
// =========================

void drawBurst(const Burst& burst)
{
    if (!burst.active)
        return;

    float brightness = burst.brightness;

    glColor3f(
        burst.r * brightness,
        burst.g * brightness,
        burst.b * brightness
    );


    // =========================
    // TYPE 1
    // CONCENTRIC SQUARES
    // =========================

    if (burst.type == 1)
    {
        for (int i = 1; i <= 3; i++)
        {
            float size =
                burst.size * (0.45f + i * 0.28f);

            glBegin(GL_LINE_LOOP);

            glVertex2f(
                burst.x - size,
                burst.y - size
            );

            glVertex2f(
                burst.x + size,
                burst.y - size
            );

            glVertex2f(
                burst.x + size,
                burst.y + size
            );

            glVertex2f(
                burst.x - size,
                burst.y + size
            );

            glEnd();
        }
    }


    // =========================
    // TYPE 2
    // DIAMOND LATTICE
    // =========================

    else if (burst.type == 2)
    {
        for (int i = 0; i < 8; i++)
        {
            float angle =
                (2.0f * PI / 8.0f) * i;

            float dx =
                cos(angle) * burst.size;

            float dy =
                sin(angle) * burst.size;

            glBegin(GL_LINES);

            glVertex2f(
                burst.x,
                burst.y
            );

            glVertex2f(
                burst.x + dx,
                burst.y + dy
            );

            glEnd();
        }

        // Diamond around center
        float size = burst.size * 0.7f;

        glBegin(GL_LINE_LOOP);

        glVertex2f(
            burst.x,
            burst.y + size
        );

        glVertex2f(
            burst.x + size,
            burst.y
        );

        glVertex2f(
            burst.x,
            burst.y - size
        );

        glVertex2f(
            burst.x - size,
            burst.y
        );

        glEnd();
    }


    // =========================
    // TYPE 3
    // STARBURST TRIANGLES
    // =========================

    else if (burst.type == 3)
    {
        for (int i = 0; i < 8; i++)
        {
            float angle =
                (2.0f * PI / 8.0f) * i;

            float dx =
                cos(angle) * burst.size;

            float dy =
                sin(angle) * burst.size;

            float sideAngle =
                angle + PI / 2.0f;

            float sideX =
                cos(sideAngle) *
                burst.size * 0.18f;

            float sideY =
                sin(sideAngle) *
                burst.size * 0.18f;

            glBegin(GL_TRIANGLES);

            glVertex2f(
                burst.x + dx,
                burst.y + dy
            );

            glVertex2f(
                burst.x + sideX,
                burst.y + sideY
            );

            glVertex2f(
                burst.x - sideX,
                burst.y - sideY
            );

            glEnd();
        }
    }
}


// =========================
// SPAWN BURST
// =========================

void spawnBurst(
    int type,
    float x,
    float y
)
{
    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (!bursts[i].active)
        {
            bursts[i].active = true;

            bursts[i].type = type;

            bursts[i].x = x;
            bursts[i].y = y;

            bursts[i].size = 0.02f;

            bursts[i].brightness = 1.0f;

            // Random bright color
            int color =
                rand() % 6;

            if (color == 0)
            {
                bursts[i].r = 1.0f;
                bursts[i].g = 0.25f;
                bursts[i].b = 0.25f;
            }
            else if (color == 1)
            {
                bursts[i].r = 1.0f;
                bursts[i].g = 0.75f;
                bursts[i].b = 0.15f;
            }
            else if (color == 2)
            {
                bursts[i].r = 0.3f;
                bursts[i].g = 0.8f;
                bursts[i].b = 1.0f;
            }
            else if (color == 3)
            {
                bursts[i].r = 0.5f;
                bursts[i].g = 1.0f;
                bursts[i].b = 0.4f;
            }
            else if (color == 4)
            {
                bursts[i].r = 0.8f;
                bursts[i].g = 0.35f;
                bursts[i].b = 1.0f;
            }
            else
            {
                bursts[i].r = 1.0f;
                bursts[i].g = 0.4f;
                bursts[i].b = 0.7f;
            }

            return;
        }
    }
}


// =========================
// UPDATE BURSTS
// =========================

void updateBursts(int value)
{
    bool anyActive = false;

    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (bursts[i].active)
        {
            anyActive = true;

            // Expand
            bursts[i].size += 0.018f;

            // Fade
            bursts[i].brightness -= 0.018f;

            // Remove expired burst
            if (bursts[i].brightness <= 0.0f)
            {
                bursts[i].active = false;
            }
        }
    }

    if (anyActive)
    {
        glutPostRedisplay();
    }

    // Keep checking for active animations
    glutTimerFunc(
        16,
        updateBursts,
        0
    );
}


// =========================
// DRAW SIDEBAR / HUD
// =========================

void drawSidebar()
{
    // Sidebar background
    glColor3f(
        0.025f,
        0.025f,
        0.05f
    );

    glBegin(GL_QUADS);

    glVertex2f(0.70f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(0.70f, -1.0f);

    glEnd();


    // Sidebar text
    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    drawText(
        0.74f,
        0.86f,
        "NIGHT SKY"
    );

    drawText(
        0.74f,
        0.77f,
        "FIREWORKS"
    );


    drawText(
        0.74f,
        0.62f,
        "CONTROLS"
    );

    drawText(
        0.74f,
        0.53f,
        "SPACE  Random burst"
    );

    drawText(
        0.74f,
        0.44f,
        "1  Square burst"
    );

    drawText(
        0.74f,
        0.35f,
        "2  Diamond burst"
    );

    drawText(
        0.74f,
        0.26f,
        "3  Starburst"
    );


    // Count active bursts
    int activeCount = 0;

    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (bursts[i].active)
            activeCount++;
    }

    drawText(
        0.74f,
        0.08f,
        "Active bursts: " +
        to_string(activeCount)
    );


    drawText(
        0.74f,
        -0.10f,
        "Press 1, 2, 3"
    );

    drawText(
        0.74f,
        -0.19f,
        "or SPACE"
    );

    drawText(
        0.74f,
        -0.35f,
        "Enjoy the"
    );

    drawText(
        0.74f,
        -0.44f,
        "night sky."
    );
}


// =========================
// DISPLAY
// =========================

void display()
{
    // Night sky background
    glClearColor(
        0.005f,
        0.008f,
        0.025f,
        1.0f
    );

    glClear(
        GL_COLOR_BUFFER_BIT
    );


    // Background
    drawStars();

    drawGround();


    // Fireworks
    for (int i = 0; i < MAX_BURSTS; i++)
    {
        drawBurst(
            bursts[i]
        );
    }


    // Sidebar
    drawSidebar();


    glFlush();
}


// =========================
// KEYBOARD
// =========================

void keyboard(
    unsigned char key,
    int x,
    int y
)
{
    // Random position
    float burstX =
        -0.55f +
        (rand() / (float)RAND_MAX) * 1.15f;

    float burstY =
        -0.50f +
        (rand() / (float)RAND_MAX) * 1.25f;


    // SPACE
    if (key == ' ')
    {
        int randomType =
            1 + rand() % 3;

        spawnBurst(
            randomType,
            burstX,
            burstY
        );
    }


    // Square
    else if (key == '1')
    {
        spawnBurst(
            1,
            burstX,
            burstY
        );
    }


    // Diamond
    else if (key == '2')
    {
        spawnBurst(
            2,
            burstX,
            burstY
        );
    }


    // Starburst
    else if (key == '3')
    {
        spawnBurst(
            3,
            burstX,
            burstY
        );
    }


    glutPostRedisplay();
}


// =========================
// MAIN
// =========================

int main(
    int argc,
    char** argv
)
{
    srand(
        (unsigned int)time(nullptr)
    );


    // Initialize bursts
    for (int i = 0; i < MAX_BURSTS; i++)
    {
        bursts[i].active = false;
    }


    // Generate stars
    for (int i = 0; i < STAR_COUNT; i++)
    {
        starX[i] =
            -1.0f +
            (rand() / (float)RAND_MAX) * 2.0f;

        starY[i] =
            -0.82f +
            (rand() / (float)RAND_MAX) * 1.82f;
    }


    glutInit(
        &argc,
        argv
    );

    glutInitDisplayMode(
        GLUT_SINGLE |
        GLUT_RGB
    );

    glutInitWindowSize(
        900,
        700
    );

    glutCreateWindow(
        "Night Sky Fireworks"
    );


    glutDisplayFunc(
        display
    );

    glutKeyboardFunc(
        keyboard
    );


    // Start animation timer
    glutTimerFunc(
        16,
        updateBursts,
        0
    );


    glutMainLoop();

    return 0;
}