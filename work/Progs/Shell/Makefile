CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic -Werror -Wno-unused
CFLAGS += -MMD
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -g


EXECS +=  demo-pipe demo-fork
EXECS += demo-exec shell-zero 
EXECS += shell-un demo-exec-dup   


all : $(EXECS)

run : $(EXECS)
	./$<

#-include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS)
