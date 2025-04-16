#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <cmath>
#include <cstdio>
#include <algorithm>

struct Point {
  float x, y;
};

std::vector<Point> square = {
  {0.0f, 4.0f},
  {4.0f, 4.0f},
  {4.0f, 0.0f},
  {0.0f, 0.0f},
};

float x_axis_start, x_axis_end, y_axis_start, y_axis_end;
float axis_margin_gap = 1.0f, axis_padding = 3.0f, tick_length = 0.3f;

void drawAxes() {
    glColor3f(0.7f, 0.7f, 0.7f);

    float horizontalAxisY = (y_axis_start <= 0 && y_axis_end >= 0) ? 0.0f : y_axis_start;
    float verticalAxisX   = (x_axis_start <= 0 && x_axis_end >= 0) ? 0.0f : x_axis_start;

    glBegin(GL_LINES);
      glVertex2f(x_axis_start + axis_margin_gap, horizontalAxisY + axis_margin_gap);
      glVertex2f(x_axis_end + axis_margin_gap, horizontalAxisY + axis_margin_gap);

      glVertex2f(verticalAxisX + axis_margin_gap, y_axis_start + axis_margin_gap);
      glVertex2f(verticalAxisX + axis_margin_gap, y_axis_end + axis_margin_gap);
    glEnd();
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text);
        text++;
    }
}

void drawTicks() {
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);

    for (float i = x_axis_start; i <= x_axis_end; i += 1.0f) {
      glVertex2f(i + axis_margin_gap, axis_margin_gap - tick_length / 2);
      glVertex2f(i + axis_margin_gap, axis_margin_gap + tick_length / 2);
    }
    for (float i = y_axis_start; i <= y_axis_end; i += 1.0f) {
      glVertex2f(axis_margin_gap - tick_length / 2, i + axis_margin_gap);
      glVertex2f(axis_margin_gap + tick_length / 2, i + axis_margin_gap);
    }
    glEnd();

    char buffer[10];

    for (float i = x_axis_start; i <= x_axis_end; i += 1.0f) {
      sprintf(buffer, "%d", (int)i);
      drawText(i + axis_margin_gap - 0.2f, axis_margin_gap - 2 * tick_length, buffer);
    }
    for (float i = y_axis_start; i <= y_axis_end; i += 1.0f) {
      sprintf(buffer, "%d", (int)i);
      drawText(axis_margin_gap - 2 * tick_length, i + axis_margin_gap - 0.2f, buffer);
    }
}

void drawTranslatedSquare(float tx, float ty) {
    std::cout << "Translated Square Coordinates:" << std::endl;

    std::vector<Point> scaledSquare;
    for (size_t i = 0; i < square.size(); i++) {
        Point p;
        p.x = square[i].x + tx;
        p.y = square[i].y + ty;
        scaledSquare.push_back(p);
    }

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
      for (size_t i = 0; i < scaledSquare.size(); i++) {
        glVertex2f(scaledSquare[i].x + axis_margin_gap, scaledSquare[i].y + axis_margin_gap);
      }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawTicks();
    drawTranslatedSquare(2.0f, 2.0f);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Translated Square");

    x_axis_start = -10.0f;
    x_axis_end = 10.0f;
    y_axis_start = -10.0f;
    y_axis_end = 10.0f;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(x_axis_start, x_axis_end, y_axis_start, y_axis_end);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
