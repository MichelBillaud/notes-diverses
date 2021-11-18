// @file Shape.c

#include <stdio.h>
#include <stdlib.h>

#include "Shape.h"

// fonction virtuelle

void display(void *this) {
    Shape * thisShape = this;
    thisShape->table->display(this);
}

//
