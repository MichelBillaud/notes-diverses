// @file Shape.h

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

typedef struct {
    void (*display)(void *);
    // ...
} ShapeMethodsTable;

void display_shape(void * this);

#endif
