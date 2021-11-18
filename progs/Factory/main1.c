#include <stdio.h>

#include "Rectangle.h"
#include "Circle.h"
#include "Text.h"
#include "ShapeFactory1.h"

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

void* circleBuilder(BuilderParameter parameters[])
{
    return newCircle(parameters[0].i);
}

void* rectangleBuilder(BuilderParameter parameters[])
{
    return newRectangle(parameters[0].i, parameters[1].i);
}

void *squareBuilder(BuilderParameter parameters[])
{
    return newRectangle(parameters[0].i, parameters[0].i);
}


void *textBuilder(BuilderParameter parameters[])
{
    return newText(parameters[0].i, parameters[1].i, parameters[2].s, parameters[3].i);
}

void test2()
{
    ShapeFactory factory = { .nbDescriptions = 0};
    registerBuilder(&factory, "circle", "ii", circleBuilder);
    registerBuilder(&factory, "rectangle", "ii", rectangleBuilder);
    registerBuilder(&factory, "square", "i", squareBuilder);
    registerBuilder(&factory, "text", "iisi", textBuilder);

    void *array[]=  {
        build(&factory, "circle", 10),
        build(&factory, "rectangle", 20, 30),
        build(&factory, "square", 100),
        build(&factory, "text", 200, 200, "Hello", 12)
    };

    for (int i = 0; i < 4; i++) {
        display(array[i]);
    }
}
int main()
{
    test2();
}