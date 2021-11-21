CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic -Werror
CFLAGS += -MMD
CFLAGS += -g

EXECS = main 


all : $(EXECS)

MODULES = Circle Rectangle Shape Text ShapeFactory

main: main.o $(addsuffix .o, $(MODULES))


-include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS)
