// @file ShapeFactory.h

#ifndef SHAPEFACTORY_H_INCLUDED
#define SHAPEFACTORY_H_INCLUDED


typedef union {
           int i;
		   float f;
		   char *s;
} BuilderParameter;

typedef struct {
	char * name;
	char * types;
	void * (*builder)(BuilderParameter params[]);
} BuilderDescription;

#define MAX_NB_DESCRIPTIONS_IN_FACTORY 10
#define MAX_NB_PARAMETERS_IN_BUILDER 10

typedef struct {
	int nb_descriptions;
	BuilderDescription descriptions[MAX_NB_DESCRIPTIONS_IN_FACTORY];
} ShapeFactory;


void factory_register(ShapeFactory *factory, char *name, char *types, 
	                  void * (*builder)(BuilderParameter params[]));
void * factory_build(ShapeFactory *factory, char name[], ...);

#endif
