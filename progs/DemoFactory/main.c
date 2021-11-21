#include <stdio.h>

#include "Rectangle.h"
#include "Circle.h"
#include "Text.h"

#include "ShapeFactory.h"

void test1()
{
    printf("# Test 1\n");
    Rectangle *r = new_rectangle(100, 200, 10, 20);  // position et dimensions
    display_shape(r);
    Circle    *c = new_circle(300, 300, 50);         // position et rayon
    display_shape(c);
    Text *t = new_text(200, 200, "Hello, world");
    display_text(t);
}

void * build_circle(BuilderParameter params[])
{
    return new_circle(params[0].i, params[1].i, params[2].i);
}

void * build_rectangle(BuilderParameter params[])
{
    return new_rectangle(params[0].i, params[1].i, params[2].i, params[3].i);
}

void * build_text(BuilderParameter params[])
{
    return new_text(params[0].i, params[1].i, params[2].s);
}


void test2()
{
    printf("# Test 2\n");
    ShapeFactory factory = { .nb_descriptions = 0};
    factory_register(&factory, "circle", "iii", &build_circle);
    factory_register(&factory, "rectangle", "iiii", &build_rectangle);
    factory_register(&factory, "text", "iis", &build_text);

    void * array[] = {
        factory_build(&factory, "text", 10, 20, "Hello, folks"),
        factory_build(&factory, "rectangle", 100, 100, 10, 20),
        factory_build(&factory, "circle", 100, 200, 50),
    };

    for (size_t i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
        display_shape(array[i]);
    }

}

int main()
{
    printf("# Début Tests\n");
    test1();
    test2();
    printf("# Fin Tests\n");

}