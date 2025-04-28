CC = gcc
LIBNAME = libmylib.so
VICTIM = victim
ATTACKER = attacker

all: $(LIBNAME) $(VICTIM) $(ATTACKER)

# Build the shared library
$(LIBNAME): mylib.c mylib.h
	$(CC) -fPIC -shared mylib.c -o $(LIBNAME)

# Build the victim executable, and embed rpath into it
$(VICTIM): victim.c mylib.h $(LIBNAME)
	$(CC) victim.c -L. -Wl,-rpath=. -lmylib -o $(VICTIM)

# Build the attacker executable, and embed rpath into it
$(ATTACKER): attacker.c mylib.h $(LIBNAME)
	$(CC) attacker.c -L. -Wl,-rpath=. -lmylib -o $(ATTACKER)

clean:
	rm -f *.o $(LIBNAME) $(VICTIM) $(ATTACKER)

.PHONY: all clean
