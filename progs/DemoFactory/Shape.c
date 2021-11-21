// @file Shape.c

#include <stdio.h>
#include <stdlib.h>

#include "Shape.h"


void display_shape(void * this) {
	ShapeMethodsTable **table = this;   // transtypage
	(*table)->display(this);
}
//
