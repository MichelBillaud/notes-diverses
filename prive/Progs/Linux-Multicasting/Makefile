CFLAGS += -std=c11 
CFLAGS += -Wall -Wextra -Werror

CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -MMD

binaries = sender receiver

all: $(binaries)

sender : sender.o
receiver : receiver.o

-include $(wildcard *.d)

clean:
	$(RM) *.o *.d *~

mrproper: clean
	$(RM) $(binaries)

