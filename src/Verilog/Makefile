# execs = test-half-adder test-full-adder
# execs += four-bit-adder
# execs += two-bit-adder
# execs += test-four-bit-adder
# execs += test-gen-four-bit-adder
execs += test-rs

.PHONY = clean mrproper

all: $(execs)

test-half_adder: half-adder.vl
test-half_adder: full-adder.vl half-adder.vl
two-bit-adder:  full-adder.vl half-adder.vl
test-four-bit-adder: four-bit-adder.vl full-adder.vl half-adder.vl
test-gen-four-bit-adder: gen-four-bit-adder.vl full-adder.vl half-adder.vl

%: %.vl
	iverilog -o $@ $<


clean:
	$(RM) *~

mrproper: clean
	$(RM) $(execs)
