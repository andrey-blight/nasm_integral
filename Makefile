CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
  -Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
  -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
  -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
  -Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error
CFLAGS += -m32

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm


.PHONY: all

all: main

integral: integral.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

%.o: %.asm
	nasm -f elf32 $< -o $@

%.o: %.c
	gcc -c -m32 $< -o $@

functions.o: src/functions.c
	gcc -c -m32 $< -o functions.o

parser.o: src/parser.c
	gcc -c -m32 $< -o parser.o

test.o: test/test.c
	gcc -c -m32 $< -o test.o

main: integral.o asm_funcs.o functions.o parser.o test.o
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o integral

.PHONY: test
test:
	./integral -I 1:0:1:0.001:0.5000
	./integral --test-root 1:2:0.5:1.5:0.001:1.0

.PHONY: clean
clean:
	rm -rf *.o f