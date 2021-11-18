// @file ShapeFactory.h

#ifndef SHAPEFACTORY1_H_INCLUDED
#define SHAPEFACTORY1_H_INCLUDED


typedef union {
    int i;
    float f;
    char *s;
    void *p;
} BuilderParameter;

typedef struct {
    char *name;
    char *parameterTypes;
    void * (*builder)(BuilderParameter parameters[]);
} BuilderDescription;

typedef struct {
    BuilderDescription descriptions[5];
    int nbDescriptions;
} ShapeFactory;

void registerBuilder(ShapeFactory *factory,
                char name[],
                char types[],
                void * (*builder)(BuilderParameter parameters[]) );

void *build(ShapeFactory *factory, char name[], ...);


#endif
