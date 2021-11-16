CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -MMD

EXECS = main


all : $(EXECS)

MODULES = Circle Rectangle Shape ShapeFactory
main: main.o $(addsuffix .o, $(MODULES))

-include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS)
