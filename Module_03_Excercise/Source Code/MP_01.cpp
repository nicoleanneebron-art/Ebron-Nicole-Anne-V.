#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

const float PI = 3.14159265f;

// ==========================
// GAME VARIABLES
// ==========================

float shipX = 0.0f;
float shipY = -0.8f;

int lives = 3;
int score = 0;

bool isGameOver = false;

// Asteroid 1
float asteroid1X = -0.5f;
float asteroid1Y = 1.2f;
float asteroid1Speed = 0.015f;

// Asteroid 2
float asteroid2X = 0.5f;
float asteroid2Y = 1.8f;
float asteroid2Speed = 0.025f;

// Stars
const int STAR_COUNT = 100;

float starX[STAR_COUNT];
float starY[STAR_COUNT];

// ==========================
// TEXT
// ==========================

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);

    for (char c : text)
    {
        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_18,
            c
        );
    }
}

// ==========================
// STARS
// ==========================

void drawStars()
{
    glPointSize(2.0f);

    glBegin(GL_POINTS);

    for (int i = 0; i < STAR_COUNT; i++)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(starX[i], starY[i]);
    }

    glEnd();
}

// ==========================
// NEBULA
// ==========================

void drawNebula()
{
    // Purple nebula
    glColor4f(
        0.4f,
        0.0f,
        0.6f,
        0.25f
    );

    glBegin(GL_POLYGON);

    glVertex2f(-0.95f, 0.75f);
    glVertex2f(-0.45f, 0.95f);
    glVertex2f(-0.15f, 0.45f);
    glVertex2f(-0.65f, 0.15f);

    glEnd();

    // Blue nebula
    glColor4f(
        0.0f,
        0.3f,
        0.8f,
        0.25f
    );

    glBegin(GL_POLYGON);

    glVertex2f(0.25f, -0.15f);
    glVertex2f(0.95f, -0.05f);
    glVertex2f(0.80f, -0.75f);
    glVertex2f(0.15f, -0.70f);

    glEnd();

    // Pink nebula
    glColor4f(
        0.8f,
        0.1f,
        0.5f,
        0.20f
    );

    glBegin(GL_POLYGON);

    glVertex2f(-0.85f, -0.25f);
    glVertex2f(-0.45f, -0.05f);
    glVertex2f(-0.20f, -0.45f);
    glVertex2f(-0.60f, -0.80f);

    glEnd();
}

// ==========================
// SHIP
// ==========================

void drawShip()
{
    // Main body
    glColor3f(
        0.7f,
        0.8f,
        1.0f
    );

    glBegin(GL_TRIANGLES);

    glVertex2f(
        shipX,
        shipY + 0.12f
    );

    glVertex2f(
        shipX - 0.06f,
        shipY - 0.03f
    );

    glVertex2f(
        shipX + 0.06f,
        shipY - 0.03f
    );

    glEnd();

    // Cockpit
    glColor3f(
        0.2f,
        0.9f,
        1.0f
    );

    glBegin(GL_POLYGON);

    glVertex2f(
        shipX - 0.025f,
        shipY + 0.02f
    );

    glVertex2f(
        shipX + 0.025f,
        shipY + 0.02f
    );

    glVertex2f(
        shipX + 0.018f,
        shipY + 0.065f
    );

    glVertex2f(
        shipX - 0.018f,
        shipY + 0.065f
    );

    glEnd();

    // Left wing
    glColor3f(
        0.4f,
        0.4f,
        1.0f
    );

    glBegin(GL_QUADS);

    glVertex2f(
        shipX - 0.08f,
        shipY - 0.01f
    );

    glVertex2f(
        shipX - 0.04f,
        shipY - 0.01f
    );

    glVertex2f(
        shipX - 0.05f,
        shipY - 0.08f
    );

    glVertex2f(
        shipX - 0.11f,
        shipY - 0.08f
    );

    glEnd();

    // Right wing
    glBegin(GL_QUADS);

    glVertex2f(
        shipX + 0.04f,
        shipY - 0.01f
    );

    glVertex2f(
        shipX + 0.08f,
        shipY - 0.01f
    );

    glVertex2f(
        shipX + 0.11f,
        shipY - 0.08f
    );

    glVertex2f(
        shipX + 0.05f,
        shipY - 0.08f
    );

    glEnd();

    // Engine flame
    glColor3f(
        1.0f,
        0.5f,
        0.0f
    );

    glBegin(GL_TRIANGLES);

    glVertex2f(
        shipX - 0.02f,
        shipY - 0.03f
    );

    glVertex2f(
        shipX + 0.02f,
        shipY - 0.03f
    );

    glVertex2f(
        shipX,
        shipY - 0.13f
    );

    glEnd();
}

// ==========================
// ASTEROID
// ==========================

void drawAsteroid(float x, float y)
{
    // Main asteroid
    glColor3f(
        0.55f,
        0.55f,
        0.60f
    );

    glBegin(GL_POLYGON);

    glVertex2f(x - 0.055f, y + 0.035f);
    glVertex2f(x - 0.025f, y + 0.065f);
    glVertex2f(x + 0.035f, y + 0.055f);
    glVertex2f(x + 0.065f, y + 0.015f);
    glVertex2f(x + 0.045f, y - 0.045f);
    glVertex2f(x - 0.005f, y - 0.070f);
    glVertex2f(x - 0.060f, y - 0.040f);
    glVertex2f(x - 0.070f, y + 0.005f);

    glEnd();

    // Crater 1
    glColor3f(
        0.30f,
        0.30f,
        0.35f
    );

    glBegin(GL_POLYGON);

    glVertex2f(x - 0.035f, y + 0.015f);
    glVertex2f(x - 0.010f, y + 0.030f);
    glVertex2f(x + 0.010f, y + 0.015f);
    glVertex2f(x + 0.005f, y - 0.005f);
    glVertex2f(x - 0.020f, y - 0.010f);

    glEnd();

    // Crater 2
    glBegin(GL_POLYGON);

    glVertex2f(x + 0.020f, y - 0.025f);
    glVertex2f(x + 0.040f, y - 0.015f);
    glVertex2f(x + 0.045f, y - 0.035f);
    glVertex2f(x + 0.025f, y - 0.045f);

    glEnd();
}

// ==========================
// HUD
// ==========================

void drawHUD()
{
    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    drawText(
        -0.95f,
        0.90f,
        "Lives: " + to_string(lives)
    );

    drawText(
        0.55f,
        0.90f,
        "Score: " + to_string(score)
    );
}

// ==========================
// COLLISION
// ==========================

bool checkCollision(
    float asteroidX,
    float asteroidY
)
{
    float dx =
        shipX - asteroidX;

    float dy =
        shipY - asteroidY;

    float distance =
        sqrt(
            dx * dx +
            dy * dy
        );

    return distance < 0.12f;
}

// ==========================
// ASTEROID RESPAWN
// ==========================

void respawnAsteroid(
    float& x,
    float& y
)
{
    x =
        -0.85f +
        ((float)rand() / RAND_MAX) * 1.7f;

    y = 1.2f;
}

// ==========================
// RESET GAME
// ==========================

void resetGame()
{
    shipX = 0.0f;
    shipY = -0.8f;

    lives = 3;
    score = 0;

    asteroid1X = -0.5f;
    asteroid1Y = 1.2f;

    asteroid2X = 0.5f;
    asteroid2Y = 1.8f;

    isGameOver = false;

    cout << "Game restarted!" << endl;
}

// ==========================
// UPDATE GAME
// ==========================

void updateGame(int value)
{
    if (!isGameOver)
    {
        // Move asteroids
        asteroid1Y -= asteroid1Speed;
        asteroid2Y -= asteroid2Speed;

        // Asteroid 1 reached bottom
        if (asteroid1Y < -1.2f)
        {
            score++;

            respawnAsteroid(
                asteroid1X,
                asteroid1Y
            );
        }

        // Asteroid 2 reached bottom
        if (asteroid2Y < -1.2f)
        {
            score++;

            respawnAsteroid(
                asteroid2X,
                asteroid2Y
            );
        }

        // Collision with asteroid 1
        if (checkCollision(
            asteroid1X,
            asteroid1Y))
        {
            lives--;

            cout
                << "Asteroid 1 hit the ship! "
                << "Lives remaining: "
                << lives
                << endl;

            respawnAsteroid(
                asteroid1X,
                asteroid1Y
            );
        }

        // Collision with asteroid 2
        if (checkCollision(
            asteroid2X,
            asteroid2Y))
        {
            lives--;

            cout
                << "Asteroid 2 hit the ship! "
                << "Lives remaining: "
                << lives
                << endl;

            respawnAsteroid(
                asteroid2X,
                asteroid2Y
            );
        }

        // Game over
        if (lives <= 0)
        {
            isGameOver = true;

            cout
                << "GAME OVER!"
                << endl;
        }
    }

    glutPostRedisplay();

    glutTimerFunc(
        16,
        updateGame,
        0
    );
}

// ==========================
// KEYBOARD
// ==========================

void keyboard(
    unsigned char key,
    int x,
    int y
)
{
    // Restart
    if (isGameOver)
    {
        if (key == 'r' || key == 'R')
        {
            resetGame();
        }

        return;
    }

    float step = 0.1f;

    switch (key)
    {
    case 'w':
    case 'W':
        shipY += step;
        break;

    case 's':
    case 'S':
        shipY -= step;
        break;

    case 'a':
    case 'A':
        shipX -= step;
        break;

    case 'd':
    case 'D':
        shipX += step;
        break;
    }

    // Keep ship inside the play area
    if (shipX < -0.85f)
        shipX = -0.85f;

    if (shipX > 0.85f)
        shipX = 0.85f;

    if (shipY < -0.85f)
        shipY = -0.85f;

    if (shipY > 0.80f)
        shipY = 0.80f;

    glutPostRedisplay();
}

// ==========================
// DISPLAY
// ==========================

void display()
{
    // Clear FIRST
    glClearColor(
        0.0f,
        0.0f,
        0.08f,
        1.0f
    );

    glClear(
        GL_COLOR_BUFFER_BIT
    );

    // Background
    drawStars();
    drawNebula();

    if (!isGameOver)
    {
        // Player
        drawShip();

        // Asteroids
        drawAsteroid(
            asteroid1X,
            asteroid1Y
        );

        drawAsteroid(
            asteroid2X,
            asteroid2Y
        );

        // HUD
        drawHUD();
    }
    else
    {
        // Game over screen
        glColor3f(
            1.0f,
            0.2f,
            0.2f
        );

        drawText(
            -0.35f,
            0.10f,
            "GAME OVER"
        );

        glColor3f(
            1.0f,
            1.0f,
            1.0f
        );

        drawText(
            -0.55f,
            -0.10f,
            "Press R to Restart"
        );

        drawText(
            -0.35f,
            -0.30f,
            "Final Score: " +
            to_string(score)
        );
    }

    glFlush();
}

// ==========================
// MAIN
// ==========================

int main(
    int argc,
    char** argv
)
{
    // Seed random numbers
    srand(
        (unsigned int)time(nullptr)
    );

    // Generate stars
    for (int i = 0; i < STAR_COUNT; i++)
    {
        starX[i] =
            -1.0f +
            ((float)rand() / RAND_MAX) *
            2.0f;

        starY[i] =
            -1.0f +
            ((float)rand() / RAND_MAX) *
            2.0f;
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
        800,
        600
    );

    glutCreateWindow(
        "Space Survival"
    );

    // Enable transparency for nebula
    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    glutDisplayFunc(
        display
    );

    glutKeyboardFunc(
        keyboard
    );

    glutTimerFunc(
        16,
        updateGame,
        0
    );

    glutMainLoop();

    return 0;
}