CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic -Werror -Wno-unused
CFLAGS += -MMD
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -g

VALGRIND_OPTIONS = -s -q --leak-check=full

TESTS = tests-string-array 
TESTS += tests-split-line

EXECS = mini-shell


all : tests execs

tests : $(TESTS)
	for p in $(TESTS) ; do valgrind $(VALGRIND_OPTIONS) ./$$p ; done


execs : $(EXECS)
	for p in $(EXECS) ; do ./$$p ; done
	


# composition des exécutables

tests-string-array: string-array.o
tests-split-line: split-line.o string-array.o

mini-shell: split-line.o string-array.o

# dépendances automatiques

-include $(wildcard *.d)

# utilitaires

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS) $(TESTS)
