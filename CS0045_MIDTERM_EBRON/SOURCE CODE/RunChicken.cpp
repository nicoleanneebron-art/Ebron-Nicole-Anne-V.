#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

const int WINDOW_W = 1100;
const int WINDOW_H = 650;
const float GROUND_Y = 92.0f;
const float GRAVITY = -1450.0f;
const float JUMP_FORCE = 610.0f;
const float PLAYER_X = 155.0f;
const float PI = 3.1415926535f;
const float INTRO_DURATION = 3.4f;

enum GameState { START_SCREEN, PLAYING, PAUSED, GAME_OVER };

struct Player {
    float x = PLAYER_X, y = GROUND_Y + 42.0f;
    float width = 58.0f, height = 62.0f;
    float velocityY = 0.0f;
    int jumpCount = 0;
    bool grounded = true;
};

struct Obstacle { float x, y, width, height; int type; };
struct Platform { float x, y, width, height; };
struct Egg { float x, y; bool collected; };
struct Bird { float x, y, width, height, phase; };
struct LifeChicken { float x, y, velocityY; bool falling; };

GameState state = START_SCREEN;
Player player;
std::vector<Obstacle> obstacles;
std::vector<Platform> platforms;
std::vector<Egg> eggs;
std::vector<Bird> birds;
std::vector<LifeChicken> lifeChickens;
float gameSpeed = 300.0f;
float distanceRun = 0.0f;
int eggsCollected = 0;
int bestScore = 0;
int lastTime = 0;
float cloudOffset = 0.0f;
float hillOffset = 0.0f;
float spawnX = 950.0f;
int pattern = 0;
float animationTime = 0.0f;
float playerHitCooldown = 0.0f;
bool introRunning = false;
float introTime = 0.0f;
float startGroundOffset = 0.0f;
int viewportX = 0;
int viewportY = 0;
int viewportW = WINDOW_W;
int viewportH = WINDOW_H;
int pressedMenuButton = -1;
float menuPressTimer = 0.0f;
int pendingMenuAction = 0;

void beginGame();

// Checks whether two rectangular bounds overlap.
bool overlaps(float ax, float ay, float aw, float ah,
    float bx, float by, float bw, float bh) {
    return ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by;
}

// Smoothly eases a normalized animation value.
float smoothStep(float value) {
    value = std::max(0.0f, std::min(1.0f, value));
    return value * value * (3.0f - 2.0f * value);
}

// Wraps a scrolling value so background loops remain seamless.
float seamlessOffset(float value, float period) {
    float wrapped = std::fmod(value, period);
    if (wrapped > 0.0f) wrapped -= period;
    return wrapped;
}

// Calculates the current score from distance and collected eggs.
int score() { return static_cast<int>(distanceRun) + eggsCollected * 50; }

// Sets the active OpenGL drawing color.
void setColor(float r, float g, float b, float a = 1.0f) {
    glColor4f(r, g, b, a);
}

// Draws a colored rectangular pixel-art shape.
void quad(float x, float y, float w, float h, float r, float g, float b, float a = 1.0f) {
    GLfloat vertices[] = { x, y, x + w, y, x + w, y + h, x, y + h };
    glColor4f(r, g, b, a);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

// Draws a vertical color gradient for the sky.
void verticalGradient(float x, float y, float w, float h,
    float topR, float topG, float topB,
    float bottomR, float bottomG, float bottomB) {
    glBegin(GL_QUADS);
    glColor3f(bottomR, bottomG, bottomB); glVertex2f(x, y);
    glColor3f(bottomR, bottomG, bottomB); glVertex2f(x + w, y);
    glColor3f(topR, topG, topB); glVertex2f(x + w, y + h);
    glColor3f(topR, topG, topB); glVertex2f(x, y + h);
    glEnd();
}

// Draws a filled triangle used by mountains and trees.
void triangle(float x1, float y1, float x2, float y2, float x3, float y3,
    float r, float g, float b) {
    GLfloat vertices[] = { x1, y1, x2, y2, x3, y3 };
    setColor(r, g, b);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}

// Draws a filled polygonal circle for rounded pixel-art objects.
void circle(float cx, float cy, float radius, float r, float g, float b, int segments = 24) {
    std::vector<GLfloat> vertices;
    vertices.reserve((segments + 2) * 2);
    vertices.push_back(cx); vertices.push_back(cy);
    for (int i = 0; i <= segments; ++i) {
        float a = 2.0f * PI * i / segments;
        vertices.push_back(cx + std::cos(a) * radius);
        vertices.push_back(cy + std::sin(a) * radius);
    }
    setColor(r, g, b);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices.data());
    glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

// Draws bitmap text using the specified color.
void textColor(float x, float y, const std::string& value, float r, float g, float b,
    void* font = GLUT_BITMAP_HELVETICA_18) {
    setColor(r, g, b);
    glRasterPos2f(x, y);
    for (char c : value) glutBitmapCharacter(font, c);
}

// Clears dynamic world objects and creates the initial runway.
void clearWorld() {
    obstacles.clear(); platforms.clear(); eggs.clear(); birds.clear(); lifeChickens.clear();
    spawnX = -120.0f;
    pattern = 0;
    // A generous starting runway makes the controls immediately readable.
    platforms.push_back({ -160.0f, GROUND_Y, 1050.0f, 34.0f });
    spawnX = 890.0f;
}

// Resets gameplay state, timers, counters, and world content.
void resetGame() {
    player = Player();
    gameSpeed = 300.0f;
    distanceRun = 0.0f;
    eggsCollected = 0;
    cloudOffset = hillOffset = 0.0f;
    animationTime = 0.0f;
    playerHitCooldown = 0.0f;
    introTime = 0.0f;
    introRunning = false;
    startGroundOffset = 0.0f;
    clearWorld();
}

// Adds the next procedural platform, obstacle, egg, and bird pattern.
void addPattern() {
    float x = spawnX;
    // These patterns are intentionally spaced for a double-jump to remain possible.
    if (pattern % 4 == 0) {
        // Continue the ground through the recovery lane; no large hidden gap
        // should appear between this pattern and the next one.
        platforms.push_back({ x, GROUND_Y, 430.0f, 34.0f });
        obstacles.push_back({ x + 125.0f, GROUND_Y + 34.0f, 34.0f, 62.0f, 0 });
        eggs.push_back({ x + 170.0f, GROUND_Y + 135.0f, false });
        // Leave a long recovery lane after each fence.
        spawnX = x + 430.0f;
    }
    else if (pattern % 4 == 1) {
        platforms.push_back({ x, GROUND_Y, 145.0f, 34.0f });
        // Small pit: visible and punishable, but still easy to clear with a
        // single jump when the player is watching the ground.
        platforms.push_back({ x + 185.0f, GROUND_Y, 575.0f, 34.0f });
        platforms.push_back({ x + 110.0f, GROUND_Y + 105.0f, 125.0f, 22.0f });
        obstacles.push_back({ x + 340.0f, GROUND_Y + 34.0f, 38.0f, 60.0f, 1 });
        eggs.push_back({ x + 160.0f, GROUND_Y + 158.0f, false });
        spawnX = x + 760.0f;
    }
    else if (pattern % 4 == 2) {
        platforms.push_back({ x, GROUND_Y, 175.0f, 34.0f });
        // One of the few intentional pits, wide enough to catch careless
        // jump-spamming while remaining a fair, single-jump challenge.
        platforms.push_back({ x + 255.0f, GROUND_Y, 595.0f, 34.0f });
        eggs.push_back({ x + 190.0f, GROUND_Y + 125.0f, false });
        eggs.push_back({ x + 400.0f, GROUND_Y + 105.0f, false });
        // A clear pattern gives the player time to regroup after a hazard.
        spawnX = x + 850.0f;
    }
    else {
        platforms.push_back({ x, GROUND_Y, 260.0f, 34.0f });
        platforms.push_back({ x + 285.0f, GROUND_Y + 82.0f, 180.0f, 24.0f });
        platforms.push_back({ x + 320.0f, GROUND_Y, 700.0f, 34.0f });
        obstacles.push_back({ x + 620.0f, GROUND_Y + 34.0f, 42.0f, 70.0f, 2 });
        eggs.push_back({ x + 335.0f, GROUND_Y + 145.0f, false });
        spawnX = x + 1020.0f;
    }

    // Birds appear only after the runner has built up speed. Higher speed
    // adds them more often, making repeated jumping increasingly risky.
    bool birdWave = distanceRun > 350.0f && (pattern % 3 == 0 || gameSpeed > 420.0f);
    if (birdWave) {
        float birdY = 285.0f + static_cast<float>((pattern % 3) * 58);
        birds.push_back({ x + 145.0f, birdY, 58.0f, 28.0f, animationTime + pattern * 0.7f });
        if (gameSpeed > 535.0f && pattern % 2 == 0)
            birds.push_back({ x + 285.0f, birdY + 52.0f, 58.0f, 28.0f, animationTime + pattern * 1.2f });
    }
    ++pattern;
}

// Keeps enough procedural level content generated ahead of the player.
void generateWorld() {
    while (spawnX < WINDOW_W + 900.0f) addPattern();
}

// Starts a player jump when another jump is available.
void jump() {
    if (state != PLAYING) return;
    if (player.jumpCount < 2) {
        player.velocityY = JUMP_FORCE;
        player.jumpCount++;
        player.grounded = false;
    }
}

// Ends the current run and updates the best score.
void endGame() {
    state = GAME_OVER;
    bestScore = std::max(bestScore, score());
}

// Removes one follower life and reports whether one was available.
bool spendFollowerLife() {
    for (auto it = lifeChickens.rbegin(); it != lifeChickens.rend(); ++it) {
        if (!it->falling) {
            it->falling = true;
            it->velocityY = -360.0f;
            return true;
        }
    }
    return false;
}

// Updates player physics, jumping, falling, and platform landing.
void updatePlayer(float dt) {
    float oldBottom = player.y;
    player.velocityY += GRAVITY * dt;
    player.y += player.velocityY * dt;
    player.grounded = false;

    for (const Platform& p : platforms) {
        float newBottom = player.y;
        if (player.velocityY <= 0.0f && oldBottom >= p.y + p.height - 2.0f &&
            newBottom <= p.y + p.height &&
            player.x + player.width > p.x && player.x < p.x + p.width) {
            player.y = p.y + p.height;
            player.velocityY = 0.0f;
            player.grounded = true;
            player.jumpCount = 0;
        }
    }
    if (player.y < -140.0f) endGame();
}

// Advances gameplay movement, collisions, followers, and world generation.
void updateGame(float dt) {
    animationTime += dt;
    if (playerHitCooldown > 0.0f) playerHitCooldown -= dt;
    gameSpeed = std::min(660.0f, 300.0f + distanceRun * 0.018f);
    distanceRun += gameSpeed * dt * 0.10f;
    cloudOffset -= gameSpeed * 0.12f * dt;
    hillOffset -= gameSpeed * 0.25f * dt;
    spawnX -= gameSpeed * dt;
    for (Platform& p : platforms) p.x -= gameSpeed * dt;
    for (Obstacle& o : obstacles) o.x -= gameSpeed * dt;
    for (Egg& e : eggs) e.x -= gameSpeed * dt;
    // Birds fly left under their own motion, against the chicken's direction,
    // instead of merely being carried by the scenery scroll.
    for (Bird& b : birds) {
        b.x -= (gameSpeed + 140.0f) * dt;
        b.y += std::sin(animationTime * 7.0f + b.phase) * 18.0f * dt;
    }

    updatePlayer(dt);
    bool playerHitThisFrame = false;
    bool playerHitByBird = false;
    if (playerHitCooldown <= 0.0f) {
        for (const Obstacle& o : obstacles) {
            if (overlaps(player.x + 7.0f, player.y + 4.0f, player.width - 14.0f, player.height - 6.0f,
                o.x, o.y, o.width, o.height)) {
                if (spendFollowerLife()) {
                    playerHitCooldown = 1.0f;
                    playerHitThisFrame = true;
                }
                else {
                    endGame();
                    return;
                }
                break;
            }
        }
        // Birds punish airborne spam. They face and travel left, opposite the
        // chicken's forward-facing/right-running direction.
        if (!playerHitThisFrame && !player.grounded) {
            for (Bird& b : birds) {
                if (overlaps(player.x + 7.0f, player.y + 4.0f, player.width - 14.0f, player.height - 6.0f,
                    b.x, b.y, b.width, b.height)) {
                    if (spendFollowerLife()) {
                        playerHitCooldown = 1.0f;
                        playerHitThisFrame = true;
                        playerHitByBird = true;
                        b.x = -1000.0f;
                    }
                    else {
                        endGame();
                        return;
                    }
                    break;
                }
            }
        }
    }
    for (Egg& e : eggs) {
        if (!e.collected && overlaps(player.x, player.y, player.width, player.height,
            e.x - 17.0f, e.y - 17.0f, 34.0f, 34.0f)) {
            e.collected = true;
            ++eggsCollected;
            if (eggsCollected % 5 == 0) {
                // Chicks bunch up close to the player, like a small running flock.
                float followX = player.x - 34.0f * (lifeChickens.size() + 1);
                lifeChickens.push_back({ followX, player.y, 0.0f, false });
            }
        }
    }

    // Active follower chickens mirror the player's movement. Obstacles reach
    // them just after passing the player, so a missed follower visibly costs a life.
    for (size_t i = 0; i < lifeChickens.size(); ++i) {
        LifeChicken& chicken = lifeChickens[i];
        if (!chicken.falling) {
            chicken.x = player.x - 34.0f * static_cast<float>(i + 1);
            chicken.y = player.y;
            for (const Obstacle& o : obstacles) {
                if (playerHitThisFrame) break;
                if (overlaps(chicken.x + 4.0f, chicken.y + 4.0f, 34.0f, 48.0f,
                    o.x, o.y, o.width, o.height)) {
                    chicken.falling = true;
                    chicken.velocityY = -360.0f;
                    break;
                }
            }
            for (const Bird& b : birds) {
                if (!playerHitThisFrame && !playerHitByBird && !chicken.falling &&
                    overlaps(chicken.x + 4.0f, chicken.y + 4.0f, 34.0f, 48.0f,
                        b.x, b.y, b.width, b.height)) {
                    chicken.falling = true;
                    chicken.velocityY = -360.0f;
                }
            }
        }
        else {
            chicken.velocityY += GRAVITY * dt;
            chicken.y += chicken.velocityY * dt;
        }
    }
    platforms.erase(std::remove_if(platforms.begin(), platforms.end(), [](const Platform& p) { return p.x + p.width < -160.0f; }), platforms.end());
    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const Obstacle& o) { return o.x + o.width < -80.0f; }), obstacles.end());
    eggs.erase(std::remove_if(eggs.begin(), eggs.end(), [](const Egg& e) { return e.x < -80.0f || e.collected; }), eggs.end());
    birds.erase(std::remove_if(birds.begin(), birds.end(), [](const Bird& b) { return b.x + b.width < -80.0f; }), birds.end());
    lifeChickens.erase(std::remove_if(lifeChickens.begin(), lifeChickens.end(), [](const LifeChicken& c) { return c.falling && c.y < -120.0f; }), lifeChickens.end());
    if (spawnX < WINDOW_W + 600.0f) generateWorld();
}

// Draws a layered parallax pine tree with pixel highlights.
void drawForestPine(float x, float baseY, float height, float width,
    float r, float g, float b) {
    // Fuller pixel pine made from layered branch shelves rather than one
    // smooth triangle. No trunk is drawn so the row reads as a tight forest.
    float darkR = r * 0.48f, darkG = g * 0.50f, darkB = b * 0.54f;
    float shadowR = r * 0.68f, shadowG = g * 0.70f, shadowB = b * 0.70f;
    float lightR = std::min(1.0f, r * 1.32f);
    float lightG = std::min(1.0f, g * 1.25f);
    float lightB = std::min(1.0f, b * 1.12f);
    triangle(x - width * 0.48f, baseY + height * 0.10f,
        x, baseY + height, x + width * 0.48f, baseY + height * 0.10f,
        darkR, darkG, darkB);
    triangle(x - width * 0.39f, baseY + height * 0.18f,
        x, baseY + height * 0.86f, x + width * 0.39f, baseY + height * 0.18f,
        r, g, b);
    triangle(x - width * 0.44f, baseY + height * 0.24f,
        x, baseY + height * 0.53f, x + width * 0.44f, baseY + height * 0.24f,
        shadowR, shadowG, shadowB);
    triangle(x - width * 0.36f, baseY + height * 0.39f,
        x, baseY + height * 0.69f, x + width * 0.36f, baseY + height * 0.39f,
        r * 0.88f, g * 0.90f, b * 0.90f);
    triangle(x - width * 0.27f, baseY + height * 0.55f,
        x, baseY + height * 0.84f, x + width * 0.27f, baseY + height * 0.55f,
        shadowR, shadowG, shadowB);
    triangle(x - width * 0.26f, baseY + height * 0.26f,
        x - width * 0.06f, baseY + height * 0.73f,
        x - width * 0.12f, baseY + height * 0.30f,
        lightR, lightG, lightB);
    quad(x - width * 0.33f, baseY + height * 0.22f,
        width * 0.15f, height * 0.025f, lightR, lightG, lightB);
    quad(x - width * 0.27f, baseY + height * 0.43f,
        width * 0.12f, height * 0.025f, lightR, lightG, lightB);
}

// Draws the animated sky, mountains, forest, clouds, birds, and wind marks.
void drawBackground() {
    // Smoothly blended blue sky; the hard-edged objects below preserve the pixel style.
    verticalGradient(0, 116, WINDOW_W, WINDOW_H - 116,
        0.66f, 0.88f, 0.94f,
        0.34f, 0.67f, 0.81f);
    // Blue lower strip reads as water whenever the runner crosses a gap.
    quad(0, 0, WINDOW_W, 116, 0.27f, 0.66f, 0.76f);
    for (int x = 12; x < WINDOW_W; x += 86) {
        quad(static_cast<float>(x), 28.0f + (x % 3) * 7.0f, 28.0f, 4.0f, 0.40f, 0.76f, 0.82f);
    }

    float hill = seamlessOffset(hillOffset, 940.0f);
    for (int i = -3; i < 5; ++i) {
        float x = i * 470.0f + hill;
        triangle(x, 100, x + 235, 360, x + 470, 100, 0.45f, 0.70f, 0.58f);
    }
    float hillNear = seamlessOffset(hillOffset * 1.35f, 1000.0f);
    for (int i = -3; i < 6; ++i) {
        float x = i * 500.0f + hillNear;
        triangle(x, 100, x + 250, 245, x + 500, 100, 0.28f, 0.60f, 0.42f);
    }

    // A restrained midground row of pixel pines adds depth without covering
    // the taller mountain silhouettes behind it.
    // Twelve tree slots make a complete repeat, so the wrap lands on the
    // same size/color sequence instead of changing the forest at the seam.
    float treeOffset = seamlessOffset(hillOffset * 0.72f, 984.0f);
    for (int i = -4; i < 21; ++i) {
        float x = i * 82.0f + treeOffset;
        float height = 145.0f + static_cast<float>((i + 8) % 4) * 18.0f;
        float width = 78.0f + static_cast<float>((i + 8) % 3) * 10.0f;
        float greenR = 0.12f + static_cast<float>((i + 8) % 3) * 0.025f;
        float greenG = 0.40f + static_cast<float>((i + 8) % 3) * 0.035f;
        float greenB = 0.42f + static_cast<float>((i + 8) % 2) * 0.035f;
        drawForestPine(x, 100.0f, height, width, greenR, greenG, greenB);
    }

    // Spherical pixel sun: faceted orange edge, bright yellow center, and highlight.
    circle(920, 535, 53, 1.0f, 0.55f, 0.08f, 16);
    circle(917, 539, 43, 1.0f, 0.84f, 0.16f, 16);
    circle(908, 550, 23, 1.0f, 0.93f, 0.34f, 12);
    quad(881, 531, 8, 10, 1.0f, 0.66f, 0.10f);
    quad(956, 522, 10, 8, 1.0f, 0.66f, 0.10f);
    quad(921, 474, 9, 10, 1.0f, 0.68f, 0.12f);
    quad(921, 587, 9, 10, 1.0f, 0.68f, 0.12f);

    // Pixel clouds: rectangles instead of soft circles.
    float cloud = seamlessOffset(cloudOffset, 860.0f);
    for (int i = -3; i < 6; ++i) {
        float x = i * 430.0f + cloud;
        quad(x + 18, 510, 68, 22, 1.0f, 0.95f, 0.80f);
        quad(x + 42, 532, 42, 20, 1.0f, 0.98f, 0.88f);
        quad(x + 82, 510, 48, 22, 1.0f, 0.95f, 0.80f);
        quad(x + 28, 507, 94, 5, 0.89f, 0.86f, 0.73f);
    }

    // Tiny animated birds add life to the idle sky as well as gameplay.
    float bird = seamlessOffset(cloudOffset * 0.55f, 940.0f);
    for (int i = -3; i < 6; ++i) {
        float x = i * 470.0f + bird;
        float flap = std::sin(animationTime * 8.0f + i * 1.7f);
        float wingY = flap > 0.0f ? 5.0f : -2.0f;
        quad(x + 87, 411, 13, 3, 0.12f, 0.34f, 0.40f);
        quad(x + 79, 411 + wingY, 9, 3, 0.12f, 0.34f, 0.40f);
        quad(x + 99, 411 + wingY, 9, 3, 0.12f, 0.34f, 0.40f);
        quad(x + 215, 454, 9, 2, 0.24f, 0.48f, 0.53f);
        quad(x + 209, 454 + wingY * 0.7f, 7, 2, 0.24f, 0.48f, 0.53f);
        quad(x + 223, 454 + wingY * 0.7f, 7, 2, 0.24f, 0.48f, 0.53f);
    }
    float windOffset = seamlessOffset(cloudOffset * 0.3f, 549.0f);
    for (int i = -4; i < 11; ++i) {
        float x = i * 183.0f + windOffset;
        quad(x, 372.0f + ((i + 6) % 3) * 18.0f, 24.0f, 3.0f,
            0.63f, 0.84f, 0.87f);
    }
}

// Draws platforms, obstacles, eggs, birds, and follower chickens.
void drawWorld() {
    for (const Platform& p : platforms) {
        quad(p.x, p.y, p.width, p.height, 0.34f, 0.20f, 0.09f);
        quad(p.x, p.y + p.height - 14, p.width, 14, 0.34f, 0.69f, 0.23f);
        for (float tx = p.x + 18; tx < p.x + p.width - 8; tx += 58)
            quad(tx, p.y + 12, 9, 8, 0.48f, 0.28f, 0.15f);
    }
    for (const Obstacle& o : obstacles) {
        if (o.type == 0) {
            // Wooden fence: two sturdy posts, two rails, and bright post caps.
            quad(o.x + 3, o.y, 9, o.height, 0.43f, 0.22f, 0.09f);
            quad(o.x + o.width - 12, o.y, 9, o.height, 0.43f, 0.22f, 0.09f);
            quad(o.x - 2, o.y + 19, o.width + 4, 10, 0.66f, 0.35f, 0.13f);
            quad(o.x - 2, o.y + 45, o.width + 4, 10, 0.66f, 0.35f, 0.13f);
            quad(o.x + 1, o.y + o.height - 5, 13, 7, 0.88f, 0.52f, 0.16f);
            quad(o.x + o.width - 14, o.y + o.height - 5, 13, 7, 0.88f, 0.52f, 0.16f);
            quad(o.x + 5, o.y + 7, 3, o.height - 18, 0.57f, 0.30f, 0.11f);
        }
        else if (o.type == 1) {
            // Crate with a thick rim, center plank, and corner nails.
            quad(o.x, o.y, o.width, o.height, 0.60f, 0.30f, 0.10f);
            quad(o.x + 4, o.y + 4, o.width - 8, o.height - 8, 0.71f, 0.39f, 0.13f);
            quad(o.x + 4, o.y + o.height / 2.0f - 3, o.width - 8, 6, 0.48f, 0.23f, 0.08f);
            quad(o.x + o.width / 2.0f - 3, o.y + 4, 6, o.height - 8, 0.48f, 0.23f, 0.08f);
            circle(o.x + 8, o.y + 8, 3, 0.92f, 0.72f, 0.25f, 8);
            circle(o.x + o.width - 8, o.y + o.height - 8, 3, 0.92f, 0.72f, 0.25f, 8);
        }
        else {
            // Hay bale with a darker shadow, straw layers, and a binding strap.
            quad(o.x - 3, o.y, o.width + 6, o.height - 3, 0.63f, 0.34f, 0.09f);
            quad(o.x, o.y + 5, o.width, o.height - 13, 0.94f, 0.67f, 0.18f);
            quad(o.x + 2, o.y + o.height - 18, o.width - 4, 8, 1.0f, 0.80f, 0.25f);
            quad(o.x + 3, o.y + 21, o.width - 6, 5, 0.78f, 0.43f, 0.08f);
            quad(o.x + 3, o.y + 45, o.width - 6, 5, 0.78f, 0.43f, 0.08f);
            quad(o.x + 8, o.y + 5, 5, o.height - 13, 0.82f, 0.48f, 0.08f);
            quad(o.x + o.width - 13, o.y + 5, 5, o.height - 13, 0.82f, 0.48f, 0.08f);
            quad(o.x + o.width / 2.0f - 3, o.y + 3, 6, o.height - 9, 0.56f, 0.30f, 0.06f);
            for (int i = 0; i < 4; ++i)
                quad(o.x + 4 + i * 10, o.y + o.height - 8, 5, 3, 1.0f, 0.90f, 0.40f);
        }
    }
    for (const Egg& e : eggs) if (!e.collected) {
        circle(e.x, e.y, 17, 1.0f, 0.78f, 0.10f);
        circle(e.x - 5, e.y + 6, 5, 1.0f, 0.95f, 0.58f);
    }
    for (const Bird& b : birds) {
        float flap = std::sin(animationTime * 18.0f + b.phase);
        float wingY = flap * 8.0f;
        // The beak and eye are on the left: birds fly against the chicken's
        // right-facing direction as the world scrolls left.
        quad(b.x + 14, b.y + 8, 27, 13, 0.16f, 0.27f, 0.31f);
        quad(b.x + 2, b.y + 15, 14, 8, 0.16f, 0.27f, 0.31f);
        quad(b.x - 8, b.y + 17, 10, 5, 0.94f, 0.55f, 0.12f);
        quad(b.x + 38, b.y + 15, 19, 7, 0.25f, 0.38f, 0.41f);
        quad(b.x + 25, b.y + 2 + wingY, 8, 9, 0.25f, 0.38f, 0.41f);
        quad(b.x + 38, b.y + 4 - wingY, 8, 4, 0.25f, 0.38f, 0.41f);
        quad(b.x + 12, b.y + 20, 4, 4, 0.04f, 0.05f, 0.05f);
    }
    for (size_t i = 0; i < lifeChickens.size(); ++i) {
        const LifeChicken& chicken = lifeChickens[i];
        if (!chicken.falling) {
            float chickWave = std::sin(animationTime * 13.0f + static_cast<float>(i) * 0.8f);
            float chickBob = std::fabs(chickWave) * 1.5f;
            float leftStep = std::max(0.0f, chickWave) * 3.0f;
            float rightStep = std::max(0.0f, -chickWave) * 3.0f;
            float wingLift = std::fabs(chickWave) * 2.0f;
            float cy = chicken.y + chickBob;
            quad(chicken.x + 5, cy + 8, 28, 27, 1.0f, 0.82f, 0.16f);
            quad(chicken.x + 24, cy + 29, 15, 20, 1.0f, 0.88f, 0.28f);
            quad(chicken.x + 37, chicken.y + 31, 12, 6, 0.96f, 0.54f, 0.10f);
            quad(chicken.x + 34, cy + 43, 5, 5, 0.05f, 0.05f, 0.04f);
            quad(chicken.x + 9, cy + 22 + wingLift, 16, 9, 0.91f, 0.67f, 0.09f);
            quad(chicken.x + 12, chicken.y + leftStep, 6, 10, 0.93f, 0.48f, 0.08f);
            quad(chicken.x + 28, chicken.y + rightStep, 6, 10, 0.93f, 0.48f, 0.08f);
        }
        else {
            // A falling follower is rotated visually through staggered blocks.
            quad(chicken.x + 8, chicken.y + 10, 27, 13, 1.0f, 0.82f, 0.16f);
            quad(chicken.x + 2, chicken.y + 20, 11, 6, 0.96f, 0.54f, 0.10f);
            quad(chicken.x + 31, chicken.y + 6, 6, 12, 0.93f, 0.48f, 0.08f);
        }
    }
}

// Draws the barn used during the opening scene transition.
void drawCoop() {
    float introProgress = introRunning ? introTime / INTRO_DURATION : 1.0f;
    float slide = introRunning ? -480.0f * smoothStep(introProgress) : 0.0f;
    float x = 42.0f + slide;
    float y = GROUND_Y + 34.0f;
    const float navyR = 0.04f, navyG = 0.05f, navyB = 0.16f;
    // Large pixel barn for the title scene; it shares the live ground line.
    quad(x, y, 300, 210, 0.84f, 0.08f, 0.16f);
    quad(x + 8, y + 8, 284, 194, 0.94f, 0.12f, 0.20f);

    // Dark roof outline, white trim, and red inner roof.
    triangle(x - 25, y + 208, x + 150, y + 365, x + 325, y + 208, navyR, navyG, navyB);
    triangle(x - 13, y + 213, x + 150, y + 351, x + 313, y + 213, 0.98f, 0.98f, 0.94f);
    triangle(x + 1, y + 218, x + 150, y + 338, x + 299, y + 218, 0.84f, 0.08f, 0.16f);
    quad(x - 28, y + 202, 20, 12, navyR, navyG, navyB);
    quad(x + 308, y + 202, 20, 12, navyR, navyG, navyB);

    // Horizontal red barn planks.
    for (int row = 24; row < 202; row += 25)
        quad(x + 8, y + row, 284, 5, 0.70f, 0.05f, 0.13f);
    quad(x - 5, y + 202, 310, 10, navyR, navyG, navyB);
    quad(x - 8, y - 4, 316, 9, navyR, navyG, navyB);

    // Attic windows with white frames and pixel X mullions.
    quad(x + 78, y + 143, 62, 56, 0.98f, 0.98f, 0.94f);
    quad(x + 88, y + 153, 42, 36, navyR, navyG, navyB);
    quad(x + 160, y + 143, 62, 56, 0.98f, 0.98f, 0.94f);
    quad(x + 170, y + 153, 42, 36, navyR, navyG, navyB);

    // Open doorway and two red-and-white crossed doors.
    quad(x + 91, y, 118, 137, navyR, navyG, navyB);
    quad(x + 76, y, 37, 137, 0.98f, 0.98f, 0.94f);
    quad(x + 82, y + 7, 25, 123, 0.88f, 0.08f, 0.16f);
    quad(x + 191, y, 37, 137, 0.98f, 0.98f, 0.94f);
    quad(x + 197, y + 7, 25, 123, 0.88f, 0.08f, 0.16f);

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3f(navyR, navyG, navyB);
    glVertex2f(x + 83, y + 14); glVertex2f(x + 106, y + 125);
    glVertex2f(x + 106, y + 14); glVertex2f(x + 83, y + 125);
    glVertex2f(x + 198, y + 14); glVertex2f(x + 221, y + 125);
    glVertex2f(x + 221, y + 14); glVertex2f(x + 198, y + 125);
    glVertex2f(x + 89, y + 159); glVertex2f(x + 129, y + 183);
    glVertex2f(x + 129, y + 159); glVertex2f(x + 89, y + 183);
    glVertex2f(x + 171, y + 159); glVertex2f(x + 211, y + 183);
    glVertex2f(x + 211, y + 159); glVertex2f(x + 171, y + 183);
    glEnd();
    glLineWidth(1.0f);
}

// Draws feather particles around the chicken's opening leap.
void drawStartFeathers() {
    if (!introRunning) return;
    float puff = std::fmod(introTime * 70.0f, 76.0f);
    float jumpProgress = std::min(1.0f, introTime / (INTRO_DURATION * 0.28f));
    float jumpY = std::sin(PI * jumpProgress) * 125.0f;
    float x = 105.0f + puff;
    float y = GROUND_Y + 55.0f + jumpY * 0.35f + std::sin(introTime * 11.0f) * 9.0f;
    quad(x, y, 8, 12, 1.0f, 1.0f, 0.94f);
    quad(x + 14, y + 11, 6, 10, 1.0f, 1.0f, 0.94f);
    quad(x + 30, y - 3, 7, 11, 1.0f, 1.0f, 0.94f);
}

// Draws and scrolls the continuous runway used by the start scene.
void drawStartGround() {
    // The idle scene uses a continuous runway all the way to the right edge.
    quad(0, GROUND_Y, WINDOW_W, 34, 0.34f, 0.20f, 0.09f);
    quad(0, GROUND_Y + 20, WINDOW_W, 14, 0.34f, 0.69f, 0.23f);
    float tileOffset = std::fmod(startGroundOffset, 58.0f);
    for (int tile = -1; tile < WINDOW_W / 58 + 2; ++tile) {
        float x = tile * 58.0f + tileOffset + 18.0f;
        quad(x, GROUND_Y + 9, 9, 8, 0.48f, 0.28f, 0.15f);
    }
}

// Calculates horizontal correction so menu elements keep their proportions.
float menuAspectCorrection() {
    float horizontalPixelsPerUnit = viewportW / static_cast<float>(WINDOW_W);
    float verticalPixelsPerUnit = viewportH / static_cast<float>(WINDOW_H);
    return verticalPixelsPerUnit / std::max(0.001f, horizontalPixelsPerUnit);
}

// Draws the player chicken with running, jumping, and wing animations.
void drawChicken() {
    if (state == START_SCREEN && !introRunning) return;
    float runRate = 13.0f;
    float runWave = std::sin(animationTime * runRate);
    float bob = player.grounded ? std::fabs(runWave) * 2.0f : 0.0f;
    float leftStep = player.grounded ? std::max(0.0f, runWave) * 4.0f : 0.0f;
    float rightStep = player.grounded ? std::max(0.0f, -runWave) * 4.0f : 0.0f;
    bool launchJump = state == START_SCREEN && introRunning &&
        introTime < INTRO_DURATION * 0.28f;
    bool airborne = !player.grounded || launchJump;
    float wingFlap = std::sin(animationTime * 20.0f);
    float wingLift = airborne
        ? (wingFlap * 0.5f + 0.5f) * 10.0f
        : std::fabs(runWave) * 3.0f;
    float x = player.x;
    float jumpY = 0.0f;
    if (state == START_SCREEN) {
        float progress = introRunning ? smoothStep(introTime / INTRO_DURATION) : 0.0f;
        float jumpProgress = std::min(1.0f, introTime / (INTRO_DURATION * 0.28f));
        jumpY = std::sin(PI * jumpProgress) * 125.0f;
        // Leap through the doorway while the camera and ground transition
        // into the normal gameplay scene.
        x = 91.0f + progress * 64.0f;
    }
    float y = player.y + bob + jumpY;
    // Blocky chicken silhouette, matching the reference sprite proportions.
    quad(x + 8, y + 12, 42, 42, 0.98f, 0.98f, 0.91f);
    quad(x + 18, y + 48, 34, 22, 0.98f, 0.98f, 0.91f);
    quad(x + 42, y + 36, 20, 30, 0.98f, 0.98f, 0.91f);
    quad(x + 50, y + 52, 18, 11, 0.98f, 0.98f, 0.91f);
    quad(x + 52, y + 66, 12, 7, 0.92f, 0.18f, 0.13f);
    quad(x + 34, y + 71, 8, 9, 0.92f, 0.18f, 0.13f);
    quad(x + 53, y + 47, 7, 7, 0.05f, 0.06f, 0.05f);
    quad(x + 61, y + 37, 17, 10, 0.96f, 0.56f, 0.10f);
    quad(x + 24, y + 60 + wingLift, 25, 14, 0.89f, 0.88f, 0.80f);
    quad(x + 20, y + 56 + wingLift * 0.55f, 25, 5, 0.78f, 0.76f, 0.68f);
    // Feet begin at the player's base, so they visibly touch the platform.
    quad(x + 19, y + leftStep, 8, 14 - leftStep, 0.93f, 0.50f, 0.10f);
    quad(x + 42, y + rightStep, 8, 14 - rightStep, 0.93f, 0.50f, 0.10f);
    quad(x + 12, y + leftStep, 21, 5, 0.93f, 0.50f, 0.10f);
    quad(x + 39, y + rightStep, 21, 5, 0.93f, 0.50f, 0.10f);
}

// Formats a number as a four-digit HUD value.
std::string fourDigits(int value) {
    std::ostringstream result;
    result << std::setw(4) << std::setfill('0') << std::max(0, value);
    return result.str();
}

// Draws one formatted HUD information panel.
void hudBox(float x, float y, float w, const std::string& label,
    const std::string& value, float accentR, float accentG, float accentB) {
    // Solid, evenly sized boxes keep the status bar readable at every score.
    quad(x, y, w, 48, 0.04f, 0.12f, 0.17f, 0.92f);
    quad(x, y + 43, w, 5, accentR, accentG, accentB, 1.0f);
    textColor(x + 12, y + 30, label, 0.58f, 0.82f, 0.84f, GLUT_BITMAP_HELVETICA_12);
    textColor(x + 12, y + 11, value, 1.0f, 0.91f, 0.47f, GLUT_BITMAP_HELVETICA_18);
}

// Draws the animated score, status, and control HUD elements.
void drawHud() {
    const float top = WINDOW_H - 62.0f;
    // Keep the HUD above the camera until the scene is nearly ready, then let
    // it descend smoothly with the final part of the barn transition.
    float hudProgress = 1.0f;
    if (state == START_SCREEN && introRunning) {
        hudProgress = smoothStep((introTime - 1.15f) / 1.75f);
    }

    float topHudY = (1.0f - hudProgress) * 96.0f;
    hudBox(16.0f, top + topHudY, 205, "SCORE", fourDigits(score()), 0.95f, 0.46f, 0.12f);
    hudBox(231.0f, top + topHudY, 165, "GOLDEN EGGS", fourDigits(eggsCollected), 1.0f, 0.76f, 0.12f);
    hudBox(406.0f, top + topHudY, 165, "CHICK LIVES", fourDigits(static_cast<int>(lifeChickens.size())), 0.98f, 0.62f, 0.16f);
    hudBox(581.0f, top + topHudY, 165, "RUN SPEED", fourDigits(static_cast<int>(gameSpeed)), 0.26f, 0.78f, 0.62f);
    hudBox(756.0f, top + topHudY, 328, "BEST SCORE", fourDigits(bestScore), 0.36f, 0.70f, 0.92f);

    // Separate control strip: it enters from below, gliding upward into view.
    float controlsY = -(1.0f - hudProgress) * 90.0f;
    quad(16.0f, 16.0f + controlsY, 270, 28, 0.04f, 0.12f, 0.17f, 0.84f);
    quad(16.0f, 39.0f + controlsY, 270, 5, 0.31f, 0.70f, 0.74f, 1.0f);
    textColor(28.0f, 26.0f + controlsY,
        "SPACE JUMP  |  P PAUSE / RESUME  |  R RESTART",
        0.88f, 0.96f, 0.90f, GLUT_BITMAP_HELVETICA_12);
}

// Returns the 5-by-7 pixel pattern for a supported character.
const char** pixelGlyph(char c) {
    static const char* blank[] = { "00000", "00000", "00000", "00000", "00000", "00000", "00000" };
    static const char* A[] = { "01110", "10001", "10001", "11111", "10001", "10001", "10001" };
    static const char* B[] = { "11110", "10001", "10001", "11110", "10001", "10001", "11110" };
    static const char* C[] = { "01111", "10000", "10000", "10000", "10000", "10000", "01111" };
    static const char* D[] = { "11110", "10001", "10001", "10001", "10001", "10001", "11110" };
    static const char* E[] = { "11111", "10000", "10000", "11110", "10000", "10000", "11111" };
    static const char* G[] = { "01111", "10000", "10000", "10111", "10001", "10001", "01111" };
    static const char* H[] = { "10001", "10001", "10001", "11111", "10001", "10001", "10001" };
    static const char* I[] = { "11111", "00100", "00100", "00100", "00100", "00100", "11111" };
    static const char* K[] = { "10001", "10010", "10100", "11000", "10100", "10010", "10001" };
    static const char* L[] = { "10000", "10000", "10000", "10000", "10000", "10000", "11111" };
    static const char* M[] = { "10001", "11011", "10101", "10101", "10001", "10001", "10001" };
    static const char* N[] = { "10001", "11001", "10101", "10011", "10001", "10001", "10001" };
    static const char* O[] = { "01110", "10001", "10001", "10001", "10001", "10001", "01110" };
    static const char* P[] = { "11110", "10001", "10001", "11110", "10000", "10000", "10000" };
    static const char* R[] = { "11110", "10001", "10001", "11110", "10100", "10010", "10001" };
    static const char* S[] = { "01111", "10000", "10000", "01110", "00001", "00001", "11110" };
    static const char* T[] = { "11111", "00100", "00100", "00100", "00100", "00100", "00100" };
    static const char* U[] = { "10001", "10001", "10001", "10001", "10001", "10001", "01110" };
    static const char* V[] = { "10001", "10001", "10001", "10001", "10001", "01010", "00100" };
    static const char* X[] = { "10001", "10001", "01010", "00100", "01010", "10001", "10001" };
    static const char* Y[] = { "10001", "10001", "01010", "00100", "00100", "00100", "00100" };
    static const char* N0[] = { "01110", "10001", "10011", "10101", "11001", "10001", "01110" };
    static const char* N1[] = { "00100", "01100", "00100", "00100", "00100", "00100", "01110" };
    static const char* N2[] = { "01110", "10001", "00001", "00010", "00100", "01000", "11111" };
    static const char* N3[] = { "11110", "00001", "00001", "01110", "00001", "00001", "11110" };
    static const char* N4[] = { "00010", "00110", "01010", "10010", "11111", "00010", "00010" };
    static const char* N5[] = { "11111", "10000", "10000", "11110", "00001", "00001", "11110" };
    static const char* N6[] = { "01110", "10000", "10000", "11110", "10001", "10001", "01110" };
    static const char* N7[] = { "11111", "00001", "00010", "00100", "01000", "01000", "01000" };
    static const char* N8[] = { "01110", "10001", "10001", "01110", "10001", "10001", "01110" };
    static const char* N9[] = { "01110", "10001", "10001", "01111", "00001", "00001", "01110" };
    static const char* colon[] = { "00000", "00100", "00100", "00000", "00100", "00100", "00000" };
    switch (c) {
    case 'A': return A; case 'B': return B; case 'C': return C; case 'D': return D; case 'E': return E;
    case 'G': return G;
    case 'H': return H; case 'I': return I; case 'K': return K; case 'L': return L;
    case 'M': return M; case 'N': return N; case 'O': return O; case 'P': return P;
    case 'R': return R; case 'S': return S; case 'T': return T; case 'U': return U; case 'V': return V;
    case 'X': return X; case 'Y': return Y;
    case '0': return N0; case '1': return N1; case '2': return N2; case '3': return N3;
    case '4': return N4; case '5': return N5; case '6': return N6; case '7': return N7;
    case '8': return N8; case '9': return N9; case ':': return colon;
    default: return blank;
    }
}

// Calculates the width of a custom pixel-font string.
float pixelTextWidth(const std::string& value, float scale) {
    float width = 0.0f;
    for (char c : value) width += (c == ' ' ? 4.0f : 6.0f) * scale;
    return width - scale;
}

// Draws a string using the custom pixel glyphs.
void pixelText(float x, float y, const std::string& value, float scale,
    float r, float g, float b) {
    float cursor = x;
    setColor(r, g, b);
    for (char c : value) {
        if (c == ' ') { cursor += 4.0f * scale; continue; }
        const char** glyph = pixelGlyph(c);
        for (int row = 0; row < 7; ++row) {
            for (int col = 0; col < 5; ++col) {
                if (glyph[row][col] == '1')
                    quad(cursor + col * scale, y + (6 - row) * scale,
                        scale, scale, r, g, b);
            }
        }
        cursor += 6.0f * scale;
    }
}

// Draws outlined pixel text centered around a horizontal position.
void pixelCenteredText(float centerX, float y, const std::string& value,
    float scale, float r = 0.93f, float g = 0.66f,
    float b = 0.12f) {
    float width = pixelTextWidth(value, scale);
    pixelText(centerX - width / 2.0f + scale, y + scale, value, scale,
        0.05f, 0.025f, 0.01f);
    pixelText(centerX - width / 2.0f, y, value, scale, r, g, b);
}

// Draws single-color centered pixel text without an outline layer.
void pixelCenteredTextSolid(float centerX, float y, const std::string& value,
    float scale, float r, float g, float b) {
    float width = pixelTextWidth(value, scale);
    pixelText(centerX - width / 2.0f, y, value, scale, r, g, b);
}

// Draws a textured wooden menu plank with press feedback.
void minimalWoodButton(float x, float y, float w, float h, const std::string& label) {
    // Compact, beveled plank buttons inspired by the reference menu.
    float pressOffset = pressedMenuButton == static_cast<int>(y) && menuPressTimer > 0.0f ? 4.0f : 0.0f;
    float drawY = y - pressOffset;
    quad(x + 4, drawY - 5, w, h, 0.18f, 0.07f, 0.035f);
    quad(x, drawY, w, h, 0.10f, 0.045f, 0.025f);
    quad(x + 4, drawY + 4, w - 8, h - 8, 0.67f, 0.40f, 0.21f);
    quad(x + 9, drawY + h - 10, w - 18, 5, 0.88f, 0.66f, 0.38f);
    quad(x + 9, drawY + 6, w - 18, 4, 0.43f, 0.20f, 0.095f);
    quad(x + 14, drawY + h * 0.55f, w - 46, 2, 0.56f, 0.30f, 0.15f);
    quad(x + 25, drawY + 16, 30, 2, 0.76f, 0.50f, 0.26f);
    quad(x + w - 58, drawY + h - 19, 35, 2, 0.76f, 0.50f, 0.26f);
    quad(x + 4, drawY + 10, 4, h - 20, 0.80f, 0.52f, 0.27f);
    quad(x + w - 8, drawY + 10, 4, h - 20, 0.40f, 0.18f, 0.08f);
    pixelCenteredText(x + w / 2.0f, drawY + 8.0f, label, 4.0f,
        0.93f, 0.66f, 0.12f);
}

// Draws the supports connecting stacked wooden menu planks.
void menuConnector(float x, float y, float h) {
    // Small supports give the menu the hanging-plank silhouette of a real
    // wooden game sign without bringing back the oversized barn panel.
    quad(x - 8, y, 16, h, 0.15f, 0.065f, 0.03f);
    quad(x - 4, y + 4, 8, h - 8, 0.66f, 0.43f, 0.23f);
    quad(x - 12, y + h - 5, 24, 5, 0.12f, 0.05f, 0.025f);
    quad(x - 12, y, 24, 5, 0.12f, 0.05f, 0.025f);
    quad(x - 2, y + 12, 4, 8, 0.88f, 0.68f, 0.40f);
}

// Draws the transparent two-bar pause symbol.
void pixelPauseIcon(float centerX, float centerY, float scale) {
    // Transparent pause symbol: two small outlined bars with no badge behind.
    const float barW = 1.5f * scale;
    const float barH = 4.0f * scale;
    const float gap = 1.5f * scale;
    const float totalW = barW * 2.0f + gap;
    const float left = centerX - totalW / 2.0f;
    const float darkR = 0.10f, darkG = 0.035f, darkB = 0.018f;
    const float lightR = 0.94f, lightG = 0.72f, lightB = 0.34f;
    quad(left - scale * 0.35f, centerY - scale * 0.35f,
        barW + scale * 0.7f, barH + scale * 0.7f, darkR, darkG, darkB);
    quad(left + barW + gap - scale * 0.35f, centerY - scale * 0.35f,
        barW + scale * 0.7f, barH + scale * 0.7f, darkR, darkG, darkB);
    quad(left, centerY, barW, barH, lightR, lightG, lightB);
    quad(left + barW + gap, centerY, barW, barH, lightR, lightG, lightB);
}

// Draws the start, pause, and game-over menu overlays.
void drawOverlay() {
    if (state == START_SCREEN) {
        if (introRunning) return;
        glPushMatrix();
        glTranslatef(550.0f, 325.0f, 0.0f);
        glScalef(1.0f * menuAspectCorrection(), 1.0f, 1.0f);
        glTranslatef(-550.0f, -325.0f, 0.0f);
        pixelCenteredText(550.0f, 500.0f, "RUN CHICKEN", 5.0f,
            0.93f, 0.66f, 0.12f);
        minimalWoodButton(390, 420, 320, 48, "PLAY");
        minimalWoodButton(390, 340, 320, 48, "RANKINGS");
        minimalWoodButton(390, 260, 320, 48, "CREDITS");
        minimalWoodButton(390, 180, 320, 48, "EXIT");
        menuConnector(430, 388, 32);
        menuConnector(670, 388, 32);
        menuConnector(430, 308, 32);
        menuConnector(670, 308, 32);
        menuConnector(430, 228, 32);
        menuConnector(670, 228, 32);
        glPopMatrix();
    }
    else if (state == PAUSED) {
        glPushMatrix();
        glTranslatef(550.0f, 325.0f, 0.0f);
        glScalef(1.0f * menuAspectCorrection(), 1.0f, 1.0f);
        glTranslatef(-550.0f, -325.0f, 0.0f);
        pixelPauseIcon(550.0f, 480.0f, 7.5f);
        minimalWoodButton(430, 360, 240, 42, "RESUME");
        minimalWoodButton(430, 306, 240, 42, "RESTART");
        minimalWoodButton(430, 252, 240, 42, "EXIT");
        glPopMatrix();
    }
    else if (state == GAME_OVER) {
        glPushMatrix();
        glTranslatef(550.0f, 325.0f, 0.0f);
        glScalef(1.0f * menuAspectCorrection(), 1.0f, 1.0f);
        glTranslatef(-550.0f, -325.0f, 0.0f);
        pixelCenteredTextSolid(550.0f, 470.0f, "GAME OVER", 4.0f,
            0.06f, 0.03f, 0.015f);
        std::ostringstream s; s << "SCORE " << score() << "    BEST " << bestScore;
        pixelCenteredTextSolid(550.0f, 425.0f, s.str(), 3.5f,
            0.06f, 0.03f, 0.015f);
        minimalWoodButton(430, 335, 240, 42, "RUN AGAIN");
        minimalWoodButton(430, 281, 240, 42, "EXIT");
        glPopMatrix();
    }
}

// Renders one complete frame in the correct visual layer order.
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();
    drawWorld();
    if (state == START_SCREEN) {
        drawStartGround();
        drawCoop();
        drawStartFeathers();
    }
    drawChicken();
    if (state != START_SCREEN || introRunning) drawHud();
    drawOverlay();
    glutSwapBuffers();
}

// Advances timed animation, transitions, gameplay, and redraw requests.
void timer(int) {
    int now = glutGet(GLUT_ELAPSED_TIME);
    float dt = (now - lastTime) / 1000.0f;
    lastTime = now;
    dt = std::min(dt, 0.035f);
    if (menuPressTimer > 0.0f) {
        menuPressTimer -= dt;
        if (menuPressTimer <= 0.0f) {
            pressedMenuButton = -1;
            int action = pendingMenuAction;
            pendingMenuAction = 0;
            if (action == 1 || action == 3) beginGame();
            else if (action == 2) state = PLAYING;
            else if (action == 4) std::exit(0);
        }
    }
    if (state == START_SCREEN) {
        animationTime += dt;
        if (introRunning) {
            introTime += dt;
            float introProgress = smoothStep(introTime / INTRO_DURATION);
            // The whole scene surges with the frantic sprint, then settles
            // into the normal gameplay speed during the final handoff.
            float introScrollSpeed = 900.0f * (1.0f - introProgress) + gameSpeed * introProgress;
            startGroundOffset -= introScrollSpeed * dt;
            // Keep the title scene alive underneath the launch animation so
            // the barn exits with the same parallax motion as the world.
            cloudOffset -= introScrollSpeed * 0.12f * dt;
            hillOffset -= introScrollSpeed * 0.25f * dt;
            if (introTime >= INTRO_DURATION) {
                introRunning = false;
                state = PLAYING;
                lastTime = now;
            }
        }
        else {
            // A quiet idle drift keeps the title scene alive before the run.
            cloudOffset -= 12.0f * dt;
            hillOffset -= 3.0f * dt;
        }
    }
    if (state == PLAYING) updateGame(dt);
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// Starts a fresh run and begins the barn intro transition.
void beginGame() {
    resetGame();
    introRunning = true;
    introTime = 0.0f;
    state = START_SCREEN;
    lastTime = glutGet(GLUT_ELAPSED_TIME);
}

// Depresses a menu plank and queues its delayed action.
void animateMenuButton(float buttonY, int action = 0) {
    pressedMenuButton = static_cast<int>(buttonY);
    menuPressTimer = 0.16f;
    pendingMenuAction = action;
}

// Handles keyboard controls for jumping, pausing, restarting, and quitting.
void keyboard(unsigned char key, int, int) {
    if (key == 27) std::exit(0);
    if (key == ' ' || key == 'w' || key == 'W') {
        if (state == START_SCREEN && !introRunning) beginGame();
        else if (state == PLAYING) jump();
    }
    else if (key == 'p' || key == 'P') {
        if (state == PLAYING) state = PAUSED; else if (state == PAUSED) state = PLAYING;
    }
    else if (key == 'r' || key == 'R') beginGame();
}

// Handles menu clicks and mouse-based jumping in the game viewport.
void mouse(int button, int action, int mx, int my) {
    if (button != GLUT_LEFT_BUTTON || action != GLUT_DOWN) return;
    if (mx < viewportX || mx >= viewportX + viewportW ||
        my < viewportY || my >= viewportY + viewportH) return;
    float gameX = (mx - viewportX) * WINDOW_W / static_cast<float>(viewportW);
    float gameY = WINDOW_H - (my - viewportY) * WINDOW_H / static_cast<float>(viewportH);
    bool insideMenuColumn = gameX >= 390.0f && gameX <= 710.0f;
    if (state == START_SCREEN) {
        if (insideMenuColumn && ((gameY >= 500.0f && gameY <= 548.0f) ||
            (gameY >= 420.0f && gameY <= 468.0f))) {
            animateMenuButton(gameY >= 500.0f ? 500.0f : 420.0f, 1);
        }
        else if (insideMenuColumn && gameY >= 180.0f && gameY <= 228.0f) {
            animateMenuButton(180.0f, 4);
        }
        else if (insideMenuColumn && gameY >= 340.0f && gameY <= 388.0f) {
            animateMenuButton(340.0f);
        }
        else if (insideMenuColumn && gameY >= 260.0f && gameY <= 308.0f) {
            animateMenuButton(260.0f);
        }
        return;
    }
    if (state == PAUSED) {
        if (!insideMenuColumn) return;
        if (gameY >= 360.0f && gameY <= 402.0f) {
            animateMenuButton(360.0f, 2);
        }
        else if (gameY >= 306.0f && gameY <= 348.0f) {
            animateMenuButton(306.0f, 3);
        }
        else if (gameY >= 252.0f && gameY <= 294.0f) {
            animateMenuButton(252.0f, 4);
        }
        return;
    }
    if (state == GAME_OVER) {
        if (!insideMenuColumn) return;
        if (gameY >= 335.0f && gameY <= 377.0f) {
            animateMenuButton(335.0f, 3);
        }
        else if (gameY >= 281.0f && gameY <= 323.0f) {
            animateMenuButton(281.0f, 4);
        }
        return;
    }
    if (state == PLAYING && gameX < 330 && gameY > WINDOW_H - 75) jump();
}

// Updates the fullscreen viewport and orthographic projection.
void reshape(int w, int h) {
    // Fill the entire window in fullscreen mode; do not leave letterbox bars.
    viewportX = 0;
    viewportY = 0;
    viewportW = std::max(1, w);
    viewportH = std::max(1, h);
    glViewport(viewportX, viewportY, viewportW, viewportH);
    glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluOrtho2D(0, WINDOW_W, 0, WINDOW_H);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}

// Initializes OpenGL, registers callbacks, and starts the game loop.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitWindowPosition(100, 60);
    glutCreateWindow("RUN CHICKEN! - Hybrid Runner Platformer");
    glutFullScreen();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    resetGame();
    lastTime = glutGet(GLUT_ELAPSED_TIME);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
    return 0;
}
