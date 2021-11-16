// @file Rectangle.h

#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED
#include "Shape.h"

typedef struct {
    ShapeMethodsTable *table;
    int w,h ;
} Rectangle;


void displayRectangle(void *);
Rectangle * newRectangle(int w, int h);

#endif
