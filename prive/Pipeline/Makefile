CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic -Werror -Wno-unused
CFLAGS += -MMD
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -g


TESTS += pipeline-general


EXECS += demo-pipeline
EXECS += demo-pipe demo-fork demo-pipeline
EXECS += demo-exec prog shell-zero shell-un demo-exec-dup   


all : $(EXECS)

run : $(TESTS)
	$(foreach p, $(TESTS), ./$(p))

#-include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS)
