CC=gcc
CFLAGS=-c -Wall -Werror -pedantic
LIB=-lm

all: clean solver.o solver_gen.o 
	$(CC) $(LIB) -o solver.out solver.o
	$(CC) $(LIB) -o solver_gen.out solver_gen.o
solver.o: solver.c
	$(CC) $(CFLAGS) solver.c
solver_gen.o: solver_gen.c
	$(CC) $(CFLAGS) solver_gen.c
clean:
	rm -f *.o *~ *.out solver solver_gen
