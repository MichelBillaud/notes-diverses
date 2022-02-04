CFLAGS = -std=c17 -Wall -Wextra -Werror

FOO_LIB_DIR =     ../lib
FOO_INCLUDE_DIR = ../include

CPPFLAGS += -I$(FOO_INCLUDE_DIR)

LDFLAGS +=  -L$(FOO_LIB_DIR)
LDLIBS  = -lfoo

main: main.o

run: main
	LD_LIBRARY_PATH=$(FOO_LIB_DIR) ./main

mrproper:
	$(RM) *~ *.o main
