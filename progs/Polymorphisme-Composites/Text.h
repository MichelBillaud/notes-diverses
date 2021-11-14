#ifndef TEXT_CLASS_H
#include "AbstractShape.h"

/*
  The Text Class
*/
// data
typedef struct {
	AbstractShape super;
	int x, y;
	char *string; // appartient à l'objet
} Text;

// destructor

void textDestructor(void *this);

// methods
void textDisplay(void *this);
// methods table
extern ShapeMethodsTable textMethodsTable;

// allocation
Text *newText(int id, int x, int y, char *string);


#endif