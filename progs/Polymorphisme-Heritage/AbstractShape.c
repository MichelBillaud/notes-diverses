#include <stdlib.h>
#include "AbstractShape.h"

void display(void *this) {
	AbstractShape *thisShape = this;
	thisShape->table->displayMethod(this);
}

void destruct(void *this) {
	AbstractShape *thisShape = this;
	if (thisShape->table->destructor != NULL) {
		thisShape->table->destructor(this);
	}
	free(this);
}
