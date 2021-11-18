// @file ShapeFactory1.c

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "ShapeFactory1.h"

void registerBuilder(ShapeFactory *factory,
                     char name[],
                     char types[],
                     void * (*builder)(BuilderParameter parameters[]) )
{
    factory->descriptions[factory->nbDescriptions ++]
    = (BuilderDescription) {
        .name = name,
        .parameterTypes = types,
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

    BuilderParameter parameters[10];
    va_list ap;
    va_start(ap, name);
    for(int i = 0; d->parameterTypes[i] != '\0'; i++) {
        switch (d->parameterTypes[i]) {
        case 'i' :
            parameters[i].i = va_arg(ap, int);
            break;
        case 'f' :
            parameters[i].f = va_arg(ap, double);
            break;
        case 's' :
            parameters[i].s = va_arg(ap, char *);
            break;
        case 'p' :
            parameters[i].p = va_arg(ap, void *);
            break;
        }
        va_end(ap);
    }
    return d->builder(parameters);
}


