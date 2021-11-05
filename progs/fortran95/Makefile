FC = gfortran
FFLAGS = -std=f95
FFLAGS += -Wall -Wextra -pedantic 

%: %.f95
	$(LINK.F) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.o: %.f95
	$(COMPILE.F) $(OUTPUT_OPTION) $<

execs += test_permutations

test_permutations : test_permutations.o permutations.o
	$(LINK.F) $^ $(LOADLIBES) $(LDLIBS) -o $@

test_permutations.o : permutations.o 

all : $(execs)

clean:
	$(RM) *~ *.mod *.o

mrproper: clean	
	$(RM) $(execs)
