// @file Rectangle.c

#include <stdio.h>
#include <stdlib.h>

#include "Rectangle.h"


ShapeMethodsTable rectangleMethodsTable = {
    .display = displayRectangle
};

Rectangle * newRectangle(int w, int h)
{
    Rectangle *r = malloc(sizeof(Rectangle));
    *r = (Rectangle) {
        .table = & rectangleMethodsTable,
        .w = w,
        .h = h
    };
    return r;
}

void displayRectangle(void *this)
{
    Rectangle *thisRectangle = this;
    printf("Je suis un rectangle  %d x %d\n",
           thisRectangle->w,
           thisRectangle->h);
}

