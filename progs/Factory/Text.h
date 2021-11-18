// @file Text.h

#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#include "Shape.h"

typedef struct {
    ShapeMethodsTable *table;
    int x, y;
    char *string;
    int fontSize;
} Text;


void displayText(void *);
Text * newText(int x, int y, char *string, int fontSize);

#endif
