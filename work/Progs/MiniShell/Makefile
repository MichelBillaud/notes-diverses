CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic -Werror -Wno-unused
CFLAGS += -MMD
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -g

VALGRIND_OPTIONS = -s -q --leak-check=full

TESTS = tests-stringarray 
TESTS += tests-split-line

EXECS = 


all : tests execs

tests : $(TESTS)
	for p in $(TESTS) ; do valgrind $(VALGRIND_OPTIONS) ./$$p ; done


execs : $(EXECS)
	for p in $(EXECS) ; do ./$$p ; done
	


# dépendances supplémentaires
tests-stringarray: stringarray.o
tests-split-line: split-line.o stringarray.o

-include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS) $(TESTS)
