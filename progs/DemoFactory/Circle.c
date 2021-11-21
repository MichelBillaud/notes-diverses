// @file Circle.c

#include <stdio.h>
#include <stdlib.h>

#include "Circle.h"

ShapeMethodsTable circleMethodsTable = {
    .display = & display_circle
};

Circle * new_circle(int x, int y, int radius)
{
    Circle *c = malloc(sizeof(Circle));
    *c = (Circle) {
        .table = &circleMethodsTable,   // ici
        .x = x, .y = y, .radius = radius
    };
    return c;
}

void display_circle(void * this)
{
    Circle *thisCircle = this;
    printf("circle with radius %d at (%d,%d)\n",
           thisCircle->radius,
           thisCircle->x,
           thisCircle->y);
}
