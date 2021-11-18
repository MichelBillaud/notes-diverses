// @file Text.c

#include <stdio.h>
#include <stdlib.h>

#include "Text.h"


ShapeMethodsTable textMethodsTable = {
    .display = displayText
};

Text * newText(int x, int y, char * string, int fontSize)
{
    Text *t = malloc(sizeof(Text));
    *t = (Text) {
        .table = & textMethodsTable,
        .x = x,
        .y = y,
        .string = string,
        .fontSize = fontSize
    };
    return t;
}

void displayText(void *this)
{
    Text *thisText = this;
    printf("Je suis un texte \"%s\" en (%d,%d) taille %d\n",
           thisText->string,
           thisText->x,
           thisText->y,
           thisText->fontSize);
}

