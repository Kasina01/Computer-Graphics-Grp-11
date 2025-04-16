# -----------------------------------------------------------------------------
# Imports and OpenGL/GLUT setup
# -----------------------------------------------------------------------------
import sys
import math
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

# -----------------------------------------------------------------------------
# Globals and Configuration
# -----------------------------------------------------------------------------
PI = 3.14159265

# Logical extents for our 2D coordinate system
x_axis_start, x_axis_end = -10.0, 10.0
y_axis_start, y_axis_end = -10.0, 10.0

# Styling parameters
axis_margin_gap = 1.0
tick_length = 0.3

# -----------------------------------------------------------------------------
# Data Structures
# -----------------------------------------------------------------------------
class Point:
    """
    Simple 2D point.
    """
    def __init__(self, x, y):  # Note: use __init__ not _init_
        self.x = x
        self.y = y

# -----------------------------------------------------------------------------
# Drawing Routines: Axes, Ticks, and Text
# -----------------------------------------------------------------------------
def drawAxes():
    """
    Draw the X and Y axes in gray.
    """
    glColor3f(0.7, 0.7, 0.7)
    hy = 0.0 if (y_axis_start <= 0 <= y_axis_end) else y_axis_start
    vx = 0.0 if (x_axis_start <= 0 <= x_axis_end) else x_axis_start

    glBegin(GL_LINES)
    glVertex2f(x_axis_start + axis_margin_gap, hy + axis_margin_gap)
    glVertex2f(x_axis_end   + axis_margin_gap, hy + axis_margin_gap)
    glVertex2f(vx + axis_margin_gap, y_axis_start + axis_margin_gap)
    glVertex2f(vx + axis_margin_gap, y_axis_end   + axis_margin_gap)
    glEnd()

def drawText(x, y, text):
    """
    Render bitmap text at (x, y).
    """
    glRasterPos2f(x, y)
    for ch in text:
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, ord(ch))

def drawTicks():
    """
    Draw tick marks and numeric labels along both axes.
    """
    glColor3f(0.7, 0.7, 0.7)
    glBegin(GL_LINES)
    i = x_axis_start
    while i <= x_axis_end:
        glVertex2f(i + axis_margin_gap, axis_margin_gap - tick_length/2)
        glVertex2f(i + axis_margin_gap, axis_margin_gap + tick_length/2)
        i += 1.0
    j = y_axis_start
    while j <= y_axis_end:
        glVertex2f(axis_margin_gap - tick_length/2, j + axis_margin_gap)
        glVertex2f(axis_margin_gap + tick_length/2, j + axis_margin_gap)
        j += 1.0
    glEnd()

    # Draw labels
    i = x_axis_start
    while i <= x_axis_end:
        drawText(i + axis_margin_gap - 0.2,
                 axis_margin_gap - 2*tick_length,
                 str(int(i)))
        i += 1.0
    j = y_axis_start
    while j <= y_axis_end:
        drawText(axis_margin_gap - 2*tick_length,
                 j + axis_margin_gap - 0.2,
                 str(int(j)))
        j += 1.0

# -----------------------------------------------------------------------------
# Drawing Routines: Squares (filled + optional border)
# -----------------------------------------------------------------------------
def drawSquare(points, fill_color, border_color=None):
    """
    Draw a filled polygon given by 'points', then optionally draw
    its border in 'border_color'.
    """
    # Fill
    glColor3fv(fill_color)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
    glBegin(GL_POLYGON)
    for p in points:
        glVertex2f(p.x + axis_margin_gap, p.y + axis_margin_gap)
    glEnd()

    # Border (if requested)
    if border_color:
        glColor3fv(border_color)
        glLineWidth(2.0)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
        glBegin(GL_POLYGON)
        for p in points:
            glVertex2f(p.x + axis_margin_gap, p.y + axis_margin_gap)
        glEnd()
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)

# -----------------------------------------------------------------------------
# Module‑Specific Draw Calls
# -----------------------------------------------------------------------------
def drawSquareModule():
    """
    Draw the base red square at the origin.
    """
    pts = [Point(0,4), Point(4,4), Point(4,0), Point(0,0)]
    drawSquare(pts, fill_color=(1,0,0))

def drawTranslatedSquare(tx, ty):
    """
    Draw a cream‑filled, green‑bordered square translated by (tx, ty).
    """
    base = [Point(0,4), Point(4,4), Point(4,0), Point(0,0)]
    pts = [Point(p.x + tx, p.y + ty) for p in base]
    drawSquare(pts,
               fill_color=(1.0, 0.98, 0.8),
               border_color=(0, 1, 0))

def drawRotatedTranslatedSquare(tx, ty, angle):
    """
    Draw the same square, translated by (tx, ty) and then rotated
    by 'angle' degrees about the origin.
    """
    theta = math.radians(angle)
    cosT, sinT = math.cos(theta), math.sin(theta)
    orig = [Point(0,4), Point(4,4), Point(4,0), Point(0,0)]
    rotated = []
    for p in orig:
        x_t, y_t = p.x + tx, p.y + ty
        rotated.append(Point(x_t*cosT - y_t*sinT,
                             x_t*sinT + y_t*cosT))
    drawSquare(rotated,
               fill_color=(1.0, 0.98, 0.8),
               border_color=(0, 1, 0))

# -----------------------------------------------------------------------------
# Display Callback
# -----------------------------------------------------------------------------
def display():
    """
    Clear the window and redraw axes, ticks, and all squares.
    """
    glClear(GL_COLOR_BUFFER_BIT)
    drawAxes()
    drawTicks()
    drawSquareModule()
    drawTranslatedSquare(2.0, 2.0)
    drawRotatedTranslatedSquare(2.0, 2.0, 55.0)
    glFlush()

# -----------------------------------------------------------------------------
# Main Initialization & Event Loop
# -----------------------------------------------------------------------------
def main():
    """
    Initialize GLUT, create the window, set up the projection,
    register callbacks, and enter the main loop.
    """
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(600, 600)
    glutInitWindowPosition(100, 100)
    glutCreateWindow(b"Rotating Translated Square (PyOpenGL)")

    glClearColor(0.0, 0.0, 0.0, 1.0)
    gluOrtho2D(x_axis_start, x_axis_end,
               y_axis_start, y_axis_end)

    glutDisplayFunc(display)
    glutMainLoop()

# Entry point guard
if __name__ == "__main__":
    main()
