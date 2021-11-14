// file: Circle.c
#include <stdlib.h>
#include <stdio.h>

#include "Circle.h"
// methods
void circleDisplay(void *this) {
	Circle *thisCircle = this;
	printf("%d : Circle at (%d,%d) radius %d\n",
		   thisCircle->super.id,
		   thisCircle->x,
		   thisCircle->y,
		   thisCircle->radius);
}

// methods table
ShapeMethodsTable circleMethodsTable =  {
	.displayMethod = & circleDisplay,
	.destructor = NULL
};

// allocation
Circle *newCircle(int id, int x, int y, int radius) {
	Circle * thisCircle = malloc(sizeof(Circle));
	*thisCircle  = (Circle) {
		.super = (AbstractShape){&circleMethodsTable, id},
		.x = x,
		.y = y,
		.radius = radius
	};
	return thisCircle;
}
