// @file ShapeFactory.c

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "ShapeFactory.h"

void registerBuilder(ShapeFactory *factory,
                     char name[],
                     int nbArgs,
                     void * (*builder)(int parameters[]) )
{
    factory->descriptions[factory->nbDescriptions ++]
    = (BuilderDescription) {
        .name = name,
        .nbArgs = nbArgs,
        .builder = builder
    };
}

void * build(ShapeFactory *factory, char name[], ...)
{
    int index = 0;
    while ((index < factory->nbDescriptions)
            && (strcmp(name, factory->descriptions[index].name) != 0)) {
        index++;
    }

    if (index == factory->nbDescriptions) return NULL;
    BuilderDescription *d = & factory->descriptions[index];
    
    int parameters[10];
    va_list ap;
    va_start(ap, name);
    for(int i = 0; i < d->nbArgs; i++) {
        parameters[i] = va_arg(ap, int);
    }
    va_end(ap);

    return d->builder(parameters);
}

