// @file Rectangle.h

#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "Shape.h"

typedef struct {
    ShapeMethodsTable *table;  // ici
    int x, y;
    int w, h;
} Rectangle;

Rectangle * new_rectangle(int x, int y, int w, int h);
void display_rectangle(void *this);
#endif
