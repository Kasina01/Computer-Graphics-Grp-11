# Frame Buffer & OpenGL Transformations Assignment

This repository contains solutions to a computer graphics assignment involving frame buffer memory calculations and OpenGL graphical transformations. The project includes Python and C++ implementations along with write-ups explaining the approach.

## 🔢 Question A: Frame Buffer Address Calculation

### Problem Summary
Given a video monitor of size 12 inches by 14 inches with a resolution of 120 pixels per inch and each pixel using 4 bits of storage, determine the memory address of a pixel located at coordinates (x, y). The frame buffer begins at address 0.

### Approach
- Total pixels = width × height × resolution²
- Bits per pixel = 4 → bytes per pixel = 0.5
- Address calculation:  
  `address = ((y * screen_width_pixels) + x) * 0.5`
  

## 🧱 Question B: OpenGL Shape Transformation

### Problem Summary
Draw a figure with vertices A(0, 4), B(3, 4), C(4, 0), D(0, 0). Perform the following transformations:
1. Translate by (2, 2)
2. Render with a green border and cream inner fill
3. Rotate the translated figure by 55 degrees

### Approach
- Use OpenGL in C++ for rendering and transformation
- Translation and rotation are applied 
