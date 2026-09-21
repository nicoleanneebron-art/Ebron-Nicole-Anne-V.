#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>

const int WINDOW_WIDTH = 1400;
const int WINDOW_HEIGHT = 600;

struct Course {
    const char* code;
    const char* title;
    const char* section;
    const char* units;
    const char* days;
    const char* time;
    const char* room;
};

const Course courses[] = {
    { "CS0011", "MOBILE PROGRAMMING", "TN35", "3", "M / W",
     "11:00:00-12:50:00 / 11:00:00-12:50:00", "F608 / F1209" },
    { "CS0016", "NETWORK AND COMMUNICATIONS 2A", "TN35", "3", "T / W",
     "17:00:00-18:50:00 / 17:00:00-18:50:00", "ONLINE / F1101" },
    { "CS0019", "MODELING AND SIMULATION", "TN35", "3", "F / T",
     "11:00:00-12:50:00 / 11:00:00-12:50:00", "ONLINE / ONLINE" },
    { "CS0025", "SOFTWARE ENGINEERING 1", "TN35", "3", "F / TH",
     "13:00:00-15:50:00 / 15:00:00-18:50:00", "ONLINE / E609" },
    { "CS0045", "CS ELECTIVE - COMPUTER GRAPHICS AND VISUAL COMPUTING", "TN35", "3", "M / TH",
     "13:00:00-14:50:00 / 13:00:00-14:50:00", "E601 / E610" },
    { "CS0053", "CS SPECIALIZATION 2 - PROGRAMMING TOOLS AND TECHNIQUES", "TN35", "3", "M / TH",
     "07:00:00-08:50:00 / 07:00:00-08:50:00", "F702 / F609" },
    { "GED0075", "LINEAR ALGEBRA", "TN25", "3", "F / T",
     "07:00:00-08:50:00 / 07:00:00-08:50:00", "ONLINE / ONLINE" }
};

// Sets the current OpenGL drawing color using RGB values from 0.0 to 1.0.
void color(float r, float g, float b) {
    glColor3f(r, g, b);
}

// Draws one solid rectangle using the current drawing color.
void rectangle(float left, float top, float right, float bottom) {
    glBegin(GL_QUADS);
    glVertex2f(left, top);
    glVertex2f(right, top);
    glVertex2f(right, bottom);
    glVertex2f(left, bottom);
    glEnd();
}

// Draws a rectangle that smoothly blends from a top color to a bottom color.
void gradientRectangle(float left, float top, float right, float bottom,
    float topR, float topG, float topB,
    float bottomR, float bottomG, float bottomB) {
    glBegin(GL_QUADS);
    color(topR, topG, topB);
    glVertex2f(left, top);
    glVertex2f(right, top);
    color(bottomR, bottomG, bottomB);
    glVertex2f(right, bottom);
    glVertex2f(left, bottom);
    glEnd();
}

// Draws a string at the given screen position with a GLUT bitmap font.
void drawText(float x, float y, const std::string& text,
    void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (char character : text)
        glutBitmapCharacter(font, character);
}

// Calculates a string's pixel width so it can be aligned precisely.
int textWidth(const std::string& text, void* font) {
    int width = 0;
    for (char character : text)
        width += glutBitmapWidth(font, character);
    return width;
}

// Draws a string horizontally centered around a requested X position.
void drawCenteredText(float centerX, float y, const std::string& text,
    void* font = GLUT_BITMAP_HELVETICA_18) {
    drawText(centerX - textWidth(text, font) / 2.0f, y, text, font);
}

// Draws the student and enrollment details in two clean information columns.
void drawStudentInformation() {
    color(0.08f, 0.16f, 0.23f);
    void* infoFont = GLUT_BITMAP_HELVETICA_18;

    drawText(22, 35, "Enrollment Status :", infoFont);
    color(0.08f, 0.48f, 0.35f);
    drawText(178, 35, "ENROLLED", infoFont);

    color(0.08f, 0.16f, 0.23f);
    drawText(22, 70, "Student # : 202410023", infoFont);
    drawText(22, 105, "Name : EBRON, NICOLE ANNE VILLANO", infoFont);
    drawText(22, 140, "Phone : 09777978673    Zip Code : 1610", infoFont);
    drawText(22, 175, "Classification :", infoFont);

    drawText(700, 70, "College : COMPUTER STUDIES    Program : BSCSSE", infoFont);
    drawText(700, 105, "Year Level : 2    1st term, SY 26-27", infoFont);
    drawText(700, 140, "Address : 32 Sage St. Dreamhomes Subd. Brgy. Dela Paz Pasig City", infoFont);
}

// Draws the course header, alternating course rows, borders, and total units.
void drawTable() {
    const float left = 20.0f;
    const float right = 1380.0f;
    const float tableTop = 205.0f;
    const float headerBottom = 250.0f;
    const float rowHeight = 42.0f;

    gradientRectangle(left, tableTop, right, headerBottom,
        0.78f, 0.91f, 0.92f,
        0.70f, 0.87f, 0.82f);

    for (int i = 0; i < 7; i++) {
        float top = headerBottom + i * rowHeight;
        float bottom = top + rowHeight;

        if (i % 2 == 0)
            color(0.98f, 1.00f, 1.00f);
        else
            color(0.93f, 0.97f, 0.96f);
        rectangle(left, top, right, bottom);

        color(0.82f, 0.88f, 0.87f);
        glBegin(GL_LINES);
        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glEnd();
    }

    float totalTop = headerBottom + 7 * rowHeight;
    color(0.91f, 0.95f, 0.93f);
    rectangle(left, totalTop, right, 580.0f);

    color(0.22f, 0.38f, 0.42f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(left, tableTop);
    glVertex2f(right, tableTop);
    glVertex2f(right, 580.0f);
    glVertex2f(left, 580.0f);
    glEnd();

    color(0.06f, 0.18f, 0.23f);
    drawText(32, 234, "Courses");
    drawText(125, 234, "Title");
    drawCenteredText(730, 234, "Section");
    drawCenteredText(805, 234, "Units");
    drawCenteredText(870, 234, "Days");
    drawCenteredText(1080, 234, "Time");
    drawCenteredText(1310, 234, "Room");

    for (int i = 0; i < 7; i++) {
        float baseline = headerBottom + i * rowHeight + 27.0f;
        const Course& course = courses[i];

        color(0.08f, 0.16f, 0.22f);
        drawText(45, baseline, course.code);
        drawText(125, baseline, course.title);
        drawCenteredText(730, baseline, course.section);
        drawCenteredText(805, baseline, course.units);
        drawCenteredText(870, baseline, course.days);
        drawCenteredText(1080, baseline, course.time);
        drawCenteredText(1310, baseline, course.room);
    }

    color(0.05f, 0.28f, 0.27f);
    drawText(32, 570, "TOTAL UNITS 21", GLUT_BITMAP_HELVETICA_18);
}

// Clears the window and draws the complete student-information interface.
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    gradientRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
        0.96f, 0.98f, 1.00f,
        0.92f, 0.97f, 0.95f);

    drawStudentInformation();
    drawTable();
    glutSwapBuffers();
}

// Updates the viewport and keeps the interface in its designed coordinate system.
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Initializes GLUT, creates the window, and starts the display event loop.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Student Information");

    glClearColor(0.95f, 0.98f, 0.97f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
