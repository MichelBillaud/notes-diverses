#include <stdio.h>

#include "Rectangle.h"
#include "Circle.h"
#include "ShapeFactory.h"

void test1()
{
    void *array[]=  {
        newCircle(10),
        newRectangle(20,30)

    };

    for (int i = 0; i < 2; i++) {
        display(array[i]);
    }
}

void* circleBuilder(int parameters[])
{
    return newCircle(parameters[0]);
}

void* rectangleBuilder(int parameters[])
{
    return newRectangle(parameters[0], parameters[1]);
}

void *squareBuilder(int parameters[])
{
    return newRectangle(parameters[0], parameters[0]);
}

void test2()
{
    ShapeFactory factory = { .nbDescriptions = 0};
    registerBuilder(&factory, "circle", 1, circleBuilder);
    registerBuilder(&factory, "rectangle", 1, rectangleBuilder);
    registerBuilder(&factory, "square", 1, squareBuilder);

    void *array[]=  {
        build(&factory, "circle", 10),
        build(&factory, "rectangle", 20, 30),
        build(&factory, "square", 100)
    };

    for (int i = 0; i < 3; i++) {
        display(array[i]);
    }
}
int main()
{
    test2();
}