// @file Text.h

#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "Shape.h"

typedef struct {
    ShapeMethodsTable *table;
    int x, y;
    char *string;
} Text;

Text * new_text(int x, int y, char *string);
void display_text(void *this);

#endif
