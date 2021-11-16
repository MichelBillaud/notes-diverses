// @file Shape.h

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

typedef struct {
    void (*display)(void *this);   
} ShapeMethodsTable;

typedef struct {
    ShapeMethodsTable *table;
} Shape;

void display(void *);

#endif
