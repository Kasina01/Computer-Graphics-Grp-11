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

#define PI 3.14159265

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

void drawRotatedTranslatedSquare(float tx, float ty, float angle) {
    Point orig[4] = {
        {0.0f, 4.0f},
        {4.0f, 4.0f},
        {4.0f, 0.0f},
        {0.0f, 0.0f}
    };

    float theta = angle * (PI / 180.0f);
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    Point rotated[4];

    for (int i = 0; i < 4; i++) {
        float x_trans = orig[i].x + tx;
        float y_trans = orig[i].y + ty;

        rotated[i].x = x_trans * cosTheta - y_trans * sinTheta;
        rotated[i].y = x_trans * sinTheta + y_trans * cosTheta;
    }

    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
      for (int i = 0; i < 4; i++) {
          glVertex2f(rotated[i].x + axis_margin_gap, rotated[i].y + axis_margin_gap);
      }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawTicks();
    drawRotatedTranslatedSquare(2.0f, 2.0f, 55.0f);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotating Translated Square");

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
