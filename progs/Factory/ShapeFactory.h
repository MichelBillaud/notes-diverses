// @file ShapeFactory.h

#ifndef SHAPEFACTORY_H_INCLUDED
#define SHAPEFACTORY_H_INCLUDED


typedef struct {
    char *name;
    int nbArgs;
    void * (*builder)(int parameters[]);
} BuilderDescription;

typedef struct {
    BuilderDescription descriptions[5];
    int nbDescriptions;
} ShapeFactory;

void registerBuilder(ShapeFactory *factory,
                char name[],
                int nbArgs,
                void * (*builder)(int parameters[]) );

void *build(ShapeFactory *factory, char name[], ...);


#endif
