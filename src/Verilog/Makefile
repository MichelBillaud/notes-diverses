execs = test-half-adder test-full-adder

.PHONY = clean mrproper

all: $(execs)

test_half_adder: half-adder.vl
test_half_adder: full-adder.vl half-adder.vl

%: %.vl
	iverilog -o $@ $<


clean:
	$(RM) *~

mrproper: clean
	$(RM) $(execs)
