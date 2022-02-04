CFLAGS += -fPIC
CPPFLAGS += -Iinclude
LDFLAGS += -shared


lib/libfoo.so: build/foo.o
	$(LINK.c) $^ -o $@

build/%.o: src/%.c
		$(COMPILE.c) $< -o $@

run-tests:
	(cd tests; make mrproper ; make run)

clean:
	$(RM) *~ */*~ build/*

