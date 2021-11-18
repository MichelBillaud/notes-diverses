CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -MMD

EXECS = main main1


all : $(EXECS)

MODULES = Circle Rectangle Shape ShapeFactory

main: main.o $(addsuffix .o, $(MODULES))

main1: main1.o  Circle.o Rectangle.o Text.o Shape.o ShapeFactory1.o


-include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS)
