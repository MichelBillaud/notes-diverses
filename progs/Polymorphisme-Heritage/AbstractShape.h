#ifndef ABSTRACT_SHAPE_H
#define ABSTRACT_SHAPE_H

typedef struct {
	void (*displayMethod)(void * shapePtr);
	void (*destructor)(void *shapePtr);
} ShapeMethodsTable;

typedef struct {
	ShapeMethodsTable *table;
	int id;
} AbstractShape;

extern void display(void *this);
extern void destruct(void *this);

#endif