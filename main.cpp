#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>

const int WIDTH = 500;
const int HEIGHT = 500;
int le[HEIGHT], re[HEIGHT], flag = 0;

void init() {
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    std::fill(le, le + HEIGHT, WIDTH);
    std::fill(re, re + HEIGHT, 0);
}

void edge(float x0, float y0, float x1, float y1) {
    if (y1 < y0) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    float m = (x1 - x0) / (y1 - y0);
    float x = x0;

    for (int y = y0; y < y1; ++y) {
        if (x < le[y])
            le[y] = x;
        if (x > re[y])
            re[y] = x;
        x += m;
    }
}

void drawPolygon() {
    glColor3f(0, 0, 1);  // Blue color for the polygon outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(100, 100);  // Base left
    glVertex2f(200, 300);  // Left peak
    glVertex2f(250, 200);  // Valley dip
    glVertex2f(300, 300);  // Right peak
    glVertex2f(400, 100);  // Base right
    glEnd();
}

void fillPolygon() {
    std::fill(le, le + HEIGHT, WIDTH);
    std::fill(re, re + HEIGHT, 0);

    // Define the polygon vertices with a valley dip
    std::vector<std::pair<float, float>> vertices = {
        {100, 100}, {200, 300}, {250, 200}, {300, 300}, {400, 100}
    };

    int n = vertices.size();

    // Calculate edges
    for (int i = 0; i < n; ++i) {
        float x0 = vertices[i].first;
        float y0 = vertices[i].second;
        float x1 = vertices[(i + 1) % n].first;
        float y1 = vertices[(i + 1) % n].second;
        edge(x0, y0, x1, y1);
    }

    // Fill the polygon
    for (int y = 0; y < HEIGHT; ++y) {
        if (le[y] < re[y]) {
            for (int x = le[y]; x < re[y]; ++x) {
                glColor3f(1, 0, 0);  // Red color for the filled area
                glBegin(GL_POINTS);
                glVertex2f(x, y);
                glEnd();
            }
        }
    }
}

void display() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    drawPolygon();

    if (flag == 1) {
        fillPolygon();
    }

    glFlush();
}

void ScanMenu(int id) {
    if (id == 1)
        flag = 1;
    else if (id == 2)
        flag = 0;
    else
        exit(0);

    glutPostRedisplay();
}

void createMenu() {
    glutCreateMenu(ScanMenu);
    glutAddMenuEntry("Scan Line Fill", 1);
    glutAddMenuEntry("Exit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Mountain Polygon Fill");
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(display);
    init();
    createMenu();
    glutMainLoop();
    return 0;
}
