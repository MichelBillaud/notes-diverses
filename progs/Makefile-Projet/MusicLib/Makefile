#
# Makefile pour le sous projet MusicLib
#

CFLAGS = -std=c11 -Wall -Wextra
CFLAGS += -MMD
CPPFLAGS = -Iinclude
ARFLAGS = rv

OBJ = music_play music_stop

#lib/libmymusic.a: $(addprefix obj/,$(addsuffix .o,$(OBJ)))
#	(cd obj; ar $(ARFLAGS)  libmymusic.a  $(addsuffix .o,$(OBJ)))
#	mv obj/libmymusic.a $@

lib/libmymusic.a: $(addprefix obj/,$(addsuffix .o,$(OBJ)))
	$(AR) $(ARFLAGS) $@ $^

obj/%.o: src/%.c
	$(COMPILE.c) -o $@ $<

-include $(wildcard obj/*.d)

clean:
	$(RM) *~ */*~ */*.d */*.o

mrproper: clean
	$(RM) lib/*.a




