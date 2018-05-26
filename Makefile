

all: main.x

%.x: %.cxx
	g++ $< -o $@

.PHONY: test clean

test: main.x
	./$<

clean:
	rm -rf *.x
