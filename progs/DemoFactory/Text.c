// @file Text.c

#include <stdio.h>
#include <stdlib.h>

#include "Text.h"

ShapeMethodsTable textMethodsTable = {
    .display = &display_text
};

Text * new_text(int x, int y, char *string)
{
    Text *t = malloc(sizeof(Text));
    *t = (Text) {
        .table = &textMethodsTable,   // ici
        .x = x, .y = y, .string = string
    };
    return t;
}

void display_text(void * this)
{
    Text *thisText = this;
    printf("text \"%s\" at (%d,%d)\n",
           thisText->string,
           thisText->x,
           thisText->y);
}

//
