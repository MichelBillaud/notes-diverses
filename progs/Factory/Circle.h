// @file Circle.h

#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "Shape.h"

typedef struct {
    ShapeMethodsTable *table;
    int r;
} Circle;

void displayCircle(void *);
Circle * newCircle(int r);

#endif
