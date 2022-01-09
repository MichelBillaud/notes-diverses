CFLAGS = -std=c11 -Wall -Wextra

CPPFLAGS = -IMusicLib/include
LDLIBS  = -LMusicLib/lib/ -lmymusic

all: updates main

updates:
	(cd MusicLib ; make)

main : main.o

clean:
	$(RM) *~ *.o

mrproper: clean
	$(RM) main
	(cd MusicLib ; make mrproper)


