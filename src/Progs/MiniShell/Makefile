CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic -Werror -Wno-unused
CFLAGS += -MMD
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -g

VALGRIND_OPTIONS = -s -q --leak-check=full

TESTS = tests-ptr-array 
TESTS += tests-split-line

# EXECS = demo-boucle
EXECS += mini-shell

all : tests execs

tests : $(TESTS)
	for p in $(TESTS) ; do valgrind $(VALGRIND_OPTIONS) ./$$p ; done


execs : $(EXECS)
	for p in $(EXECS) ; do ./$$p ; done


# composition des exécutables

tests-ptr-array: ptr-array.o
tests-string-array: string-array.o
tests-split-line: split-line.o ptr-array.o

mini-shell: split-line.o ptr-array.o

# dépendances automatiques

-include $(wildcard *.d)

# utilitaires

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS) $(TESTS)
