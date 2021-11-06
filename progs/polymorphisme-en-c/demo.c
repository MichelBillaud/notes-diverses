#include <stdio.h>
#include <stdlib.h>


// tout objet polymorphe a une table de fonctions
// comme premier membre


typedef void (*ANIMAL_TALK_METHOD)(void *);
typedef void (*ANIMAL_FEED_METHOD)(void *, char *);

typedef struct {
    ANIMAL_TALK_METHOD talk;
    ANIMAL_FEED_METHOD feed;
} AnimalVtable;

typedef struct  {
    AnimalVtable *vtable; // table de pointeurs de fonctions
} Animal;


void Animal_Talk(void *this)
{
    Animal *animal = this;
    animal->vtable->talk(this);
}

void Animal_Feed(Animal *this, char *food)
{
    Animal *animal = this;
    animal->vtable->feed(this, food);
}

// -------------------------------------------
typedef struct {
    AnimalVtable *vtable;
    // les attributs vont ici
    char * name;
} Dog;

void Dog_Talk(void *this)
{
    Dog *dog = this;
    printf("%s> Wah!\n", dog->name);
}

void Dog_Feed(void *this, char * what)
{
    Dog *dog = this;
    (void) dog;
    printf("thanks for %s !\n", what);
}

AnimalVtable DogVtable = {
    .talk = & Dog_Talk,
    .feed = & Dog_Feed
};

Dog *new_Dog(char *name)
{
    Dog * p = malloc(sizeof(Dog));
    p->vtable = & DogVtable;
    p->name = name;
    return p;
}

// ---------------------------------------------
typedef struct {
    AnimalVtable *vtable;
    char *color;
} Fish;


void Fish_Talk(void *this)
{
    Fish *fish = this;
    printf("%s fish -> Bloup!\n", fish->color);
}

void Fish_Feed(void *this, char * what)
{
    Fish *fish = this;
    (void) fish;
    (void) what;
    printf("No thanks\n");
}

AnimalVtable fishVtable = {
    .talk =  & Fish_Talk,
    .feed =  & Fish_Feed
};

Fish *new_Fish(char *color)
{
    Fish * p = malloc(sizeof(Fish));
    p->vtable = & fishVtable;
    p->color = color;
    return p;
}


int main()
{
    Animal * animals[] = {
        (Animal *) new_Dog("Medor"),
        (Animal *) new_Fish("Yellow"),
        (Animal *) new_Dog("Rex")
    };

    for (int i = 0; i < 3; i++) {
        Animal_Talk(animals[i]);
        Animal_Feed(animals[i], "the kibbles"); // croquettes
    }

    for (int i = 0; i < 3; i++) {
        free(animals[i]);
    }
}
