# Copyright 2020 Darius Neatu <neatudarius@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=my_octave

build: $(TARGETS)

my_octave: my_octave.c
	$(CC) $(CFLAGS) my_octave.c tasks.c mem_manipulation.c matrix_functions.c -o my_octave


pack:
	zip -FSr 312CA_DamianMihai-Robert_Tema2.zip *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
