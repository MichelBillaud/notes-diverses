#include <stdio.h>

#include "AbstractShape.h"
#include "Circle.h"
#include "Text.h"
#include "Group.h"

int main()
{
	Circle * c = newCircle(1, 10, 20, 30);
	display(c);
	Text * t = newText(2, 100, 200, "hello");
	display(t);
	Group * g = newGroup(33);
	addElement(g, c);
	addElement(g, t);
	display(g);
	destruct(g);
	destruct(c);
	destruct(t);
}
