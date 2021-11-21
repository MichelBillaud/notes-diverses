// @file Rectangle.c

#include <stdio.h>
#include <stdlib.h>

#include "Rectangle.h"


ShapeMethodsTable rectangleMethodsTable = {
    .display = & display_rectangle
};

Rectangle * new_rectangle(int x, int y, int w, int h)
{
    Rectangle *r = malloc(sizeof(Rectangle));
    *r = (Rectangle) {
        .table = &rectangleMethodsTable,   // ici
        .x = x, .y = y, .w = w, .h = h
    };
    return r;
}

void display_rectangle(void * this)
{
    Rectangle *thisRectangle = this;
    printf("rectangle %dx%d at (%d,%d)\n",
           thisRectangle->w,
           thisRectangle->h,
           thisRectangle->x,
           thisRectangle->y);
}
//
