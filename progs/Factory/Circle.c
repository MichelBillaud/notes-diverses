// @file Circle.c

#include <stdio.h>
#include <stdlib.h>

#include "Circle.h"

ShapeMethodsTable circleMethodsTable = {
    .display = displayCircle
};

Circle * newCircle(int r)
{
    Circle * c = malloc(sizeof(Circle));
    *c = (Circle) {
        .table = & circleMethodsTable,
        .r = r
    };
    return c;
}

void displayCircle(void *this)
{
    Circle *thisCircle = this;
    printf("Je suis un cercle de rayon %d\n",
           thisCircle->r);
}
//
