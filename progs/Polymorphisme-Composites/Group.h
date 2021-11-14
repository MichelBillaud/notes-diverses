#ifndef GROUP_CLASS_H
#define GROUP_CLASS_H

/*
  The Group Class
*/
#include "AbstractShape.h"

// data
typedef struct {
	AbstractShape super;
	int size, capacity;
	void **elements;  // doesnt own
} Group;

void circleDisplay(void *this);

// methods table
extern ShapeMethodsTable groupMethodsTable;


// allocation
Group *newGroup(int id);

// extension
void addElement(Group *group, void * element);


#endif