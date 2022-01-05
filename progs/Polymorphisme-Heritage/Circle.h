#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

/*
  The Circle Class
*/
#include "AbstractShape.h"

// data
typedef struct {
	AbstractShape super;
	int x, y, radius;
} Circle;

void circleDisplay(void *this);

// methods table
extern ShapeMethodsTable circleMethodsTable;


// allocation
Circle *newCircle(int id, int x, int y, int radius);

#endif