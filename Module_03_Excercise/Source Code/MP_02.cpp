#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// =========================
// GAME VARIABLES
// =========================

float playerX = 0.0f;
float playerY = -0.65f;

float barrierX = 0.0f;
float barrierY = 1.2f;

float barrierSpeed = 0.015f;

int score = 0;

bool isGameOver = false;

// Player color
int playerColor = 0;
// 0 = Red
// 1 = Green
// 2 = Blue

// Barrier color
int barrierColor = 0;
// 0 = Red
// 1 = Green
// 2 = Blue


// =========================
// DRAW TEXT
// =========================

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);

    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}


// =========================
// DRAW PLAYER
// =========================

void drawPlayer()
{
    if (playerColor == 0)
        glColor3f(1.0f, 0.0f, 0.0f);       // Red
    else if (playerColor == 1)
        glColor3f(0.0f, 1.0f, 0.0f);       // Green
    else
        glColor3f(0.0f, 0.4f, 1.0f);       // Blue

    glBegin(GL_QUADS);

    glVertex2f(-0.12f, -0.12f);
    glVertex2f(0.12f, -0.12f);
    glVertex2f(0.12f, 0.12f);
    glVertex2f(-0.12f, 0.12f);

    glEnd();
}


// =========================
// DRAW BARRIER
// =========================

void drawBarrier()
{
    if (barrierColor == 0)
        glColor3f(1.0f, 0.0f, 0.0f);       // Red
    else if (barrierColor == 1)
        glColor3f(0.0f, 1.0f, 0.0f);       // Green
    else
        glColor3f(0.0f, 0.4f, 1.0f);       // Blue

    // Horizontal barrier
    glBegin(GL_QUADS);

    glVertex2f(barrierX - 0.45f, barrierY - 0.05f);
    glVertex2f(barrierX + 0.45f, barrierY - 0.05f);
    glVertex2f(barrierX + 0.45f, barrierY + 0.05f);
    glVertex2f(barrierX - 0.45f, barrierY + 0.05f);

    glEnd();
}


// =========================
// DRAW DASHBOARD
// =========================

void drawDashboard()
{
    string colorName;

    if (playerColor == 0)
        colorName = "RED";
    else if (playerColor == 1)
        colorName = "GREEN";
    else
        colorName = "BLUE";

    glColor3f(1.0f, 1.0f, 1.0f);

    drawText(-0.95f, 0.90f, "Score: " + to_string(score));

    drawText(-0.95f, 0.80f,
        "Player Color: " + colorName);

    drawText(-0.95f, -0.90f,
        "R = Red   G = Green   B = Blue");

    drawText(0.15f, -0.90f,
        "Match the barrier color!");

    if (isGameOver)
    {
        drawText(-0.28f, 0.10f,
            "GAME OVER");

        drawText(-0.45f, 0.00f,
            "Press R to Restart");

        drawText(-0.55f, -0.10f,
            "Mismatch! Choose the correct color.");
    }
}


// =========================
// CHECK COLOR MATCH
// =========================

bool colorsMatch()
{
    return playerColor == barrierColor;
}


// =========================
// CHECK COLLISION
// =========================

bool checkGateCollision()
{
    return (
        barrierY - 0.05f <= playerY + 0.12f &&
        barrierY + 0.05f >= playerY - 0.12f
        );
}


// =========================
// SPAWN NEXT BARRIER
// =========================

void spawnNextBarrier()
{
    barrierY = 1.2f;

    // Random color
    barrierColor = rand() % 3;
}


// =========================
// UPDATE BARRIER
// =========================

void updateBarrier(int value)
{
    if (!isGameOver)
    {
        // Move barrier downward
        barrierY -= barrierSpeed;

        // Check if barrier reached player
        if (checkGateCollision())
        {
            if (colorsMatch())
            {
                // Correct match
                score++;

                cout << "Correct match! Score: "
                    << score << endl;

                // Increase difficulty
                barrierSpeed += 0.002f;

                // Spawn next barrier
                spawnNextBarrier();
            }
            else
            {
                // Mismatch = Game Over
                isGameOver = true;

                cout << "Wrong color! Game Over." << endl;
            }
        }

        // If barrier somehow passes the player
        if (barrierY < -1.2f)
        {
            spawnNextBarrier();
        }
    }

    glutPostRedisplay();

    // Continue animation
    glutTimerFunc(16, updateBarrier, 0);
}


// =========================
// RESET GAME
// =========================

void resetGame()
{
    playerX = 0.0f;
    playerY = -0.65f;

    barrierX = 0.0f;
    barrierY = 1.2f;

    barrierSpeed = 0.015f;

    score = 0;

    playerColor = 0;

    barrierColor = rand() % 3;

    isGameOver = false;

    cout << "Game restarted." << endl;

    glutPostRedisplay();
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
    // Restart
    if (isGameOver)
    {
        if (key == 'r' || key == 'R')
        {
            resetGame();
        }

        return;
    }

    switch (key)
    {
    case 'r':
    case 'R':
        playerColor = 0;

        cout << "Player color: RED" << endl;
        break;

    case 'g':
    case 'G':
        playerColor = 1;

        cout << "Player color: GREEN" << endl;
        break;

    case 'b':
    case 'B':
        playerColor = 2;

        cout << "Player color: BLUE" << endl;
        break;
    }

    glutPostRedisplay();
}


// =========================
// DISPLAY
// =========================

void display()
{
    // Plain black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    if (!isGameOver)
    {
        drawPlayer();
        drawBarrier();
    }
    else
    {
        // Keep player and barrier visible
        // during game over
        drawPlayer();
        drawBarrier();
    }

    drawDashboard();

    glFlush();
}


// =========================
// MAIN
// =========================

int main(int argc, char** argv)
{
    srand((unsigned int)time(nullptr));

    // Random starting barrier color
    barrierColor = rand() % 3;

    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_SINGLE |
        GLUT_RGB
    );

    glutInitWindowSize(700, 700);

    glutCreateWindow(
        "Color Gate Challenge"
    );

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutTimerFunc(
        16,
        updateBarrier,
        0
    );

    glutMainLoop();

    return 0;
}