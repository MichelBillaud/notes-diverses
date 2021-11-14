#include <stdio.h>
#include <stdlib.h>
#include "Group.h"

#define MINIMUM_GROUP_CAPACITY 4
#define GROUP_GROWING_FACTOR 2

// methods
void groupDisplay(void *this)
{
    Group *thisGroup = this;
    printf("%d : Group with %d elements {\n",
           thisGroup->super.id,
           thisGroup->size
          );
    for (int i = 0; i < thisGroup->size; i++) {
        display(thisGroup->elements[i]);
    }
    printf("}\n");
}

void groupDestructor(void *this)
{
    Group *thisGroup = this;
    free(thisGroup->elements);
}

// methods table
ShapeMethodsTable groupMethodsTable =  {
    .displayMethod = & groupDisplay,
    .destructor = groupDestructor
};

// allocation
Group *newGroup(int id)
{
    Group *thisGroup  = malloc(sizeof(Group));
    *thisGroup  = (Group) {
        .super = (AbstractShape) {&groupMethodsTable, id},
        .size = 0,
        .capacity = MINIMUM_GROUP_CAPACITY,
        .elements = malloc(MINIMUM_GROUP_CAPACITY
                           * sizeof(void *))
    };
    return thisGroup;
}

void addElement(Group *group, void * element) {
	if (group->size == group->capacity) {
		group->capacity *= GROUP_GROWING_FACTOR;
		group->elements = realloc(group->elements, group->capacity * sizeof(void *));
	}
	group->elements[group->size ++] = element;
}
