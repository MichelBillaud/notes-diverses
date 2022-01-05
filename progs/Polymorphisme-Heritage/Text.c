#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Text.h"
/*
  The Text Class
*/

// destructors
void textDestructor(void *this) {
	Text *thisText = this;
	free(thisText->string);
}

// methods
void textDisplay(void *this) {
	Text *thisText = this;
	printf("%d : Text at (%d,%d) %s\n",
		   thisText->super.id,
		   thisText->x,
		   thisText->y,
		   thisText->string);
}

// methods table
ShapeMethodsTable textMethodsTable =  {
	.displayMethod = & textDisplay,
	.destructor = &textDestructor
};


// allocation
Text *newText(int id, int x, int y, char *string) {
	Text * thisText = malloc(sizeof(Text));
	*thisText = (Text) {
		.super = (AbstractShape){& textMethodsTable, id},
		.x = x,
		.y = y,
		.string = strdup(string)
	};
	return thisText;
}

