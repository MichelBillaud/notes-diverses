// @file Circle.h

#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "Shape.h"

typedef struct {
    ShapeMethodsTable *table;  // ici
    int x, y;
    int radius;
} Circle;

Circle * new_circle(int x, int y, int radius);
void display_circle(void *this);
#endif
