// @file ShapeFactory.c

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "ShapeFactory.h"

void factory_register(ShapeFactory *factory, char *name, char *types,
                      void * (*builder)(BuilderParameter params[]))
{
    factory->descriptions[factory->nb_descriptions ++] =
    (BuilderDescription) {
        .name = name,
        .types = types,
        .builder = builder
    };
}

void * factory_build(ShapeFactory *factory, char name[], ...)
{
    int index = 0;
	while ((index < factory->nb_descriptions)
	&& (strcmp(name, factory->descriptions[index].name) != 0)) {
        index++;
    }

	if (index == factory->nb_descriptions) {
		return NULL;
	}
    BuilderDescription *d = & factory->descriptions[index];

    BuilderParameter parameters[MAX_NB_PARAMETERS_IN_BUILDER];
    va_list ap;
    va_start(ap, name);
    for(int i = 0; d->types[i] != '\0'; i++) {
        switch (d->types[i]) {
        case 'i' :
            parameters[i].i = va_arg(ap, int);
            break;
        case 'f' :
            parameters[i].f = va_arg(ap, double);
            break;
        case 's' :
            parameters[i].s = va_arg(ap, char *);
            break;
        }
        va_end(ap);
    }
    return d->builder(parameters);
}
//
