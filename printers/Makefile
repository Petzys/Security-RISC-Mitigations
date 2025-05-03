# Makefile to build rdcycle, rdtime, and rdinstret test programs

# Native compiler on the RISC-V board
CC = gcc
CFLAGS = -O2

# Source files
SRCS = rdcycle.c rdtime.c rdinstret.c

# Output binaries
BINS = $(SRCS:.c=)

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BINS)