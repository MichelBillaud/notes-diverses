CFLAGS += -std=c17
CFLAGS +=  -Wall -Wextra -pedantic 
CFLAGS += -Wno-unused -Werror
CFLAGS += -D_XOPEN_SOURCE=700
#CFLAGS += -Ofast
#CFLAGS += -pg -g
CFLAGS += -MMD

# LDFLAGS += -pg -g

execs = poly-shapes 

all: $(execs)

poly-shapes: poly-shapes.o AbstractShape.o Circle.o Text.o Group.o


-include *.d

clean:
	$(RM) *.o *~ \#* *.d

mrproper: clean
	$(RM) $(execs)
