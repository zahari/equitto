CC = gcc
CFLAGS = -Wall -Werror -pedantic
LDFLAGS = -lm
EXECUTABLES = solver.out solver_gen.out

all: clean $(EXECUTABLES)
	mkdir bin/
	mv *.out bin/ 

%.out: %.o
	@echo "   $@"
	@$(CC) -o $@ $< $(LDFLAGS)

%.o: %.c
	@echo "   $@"
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o *~ *.out bin/
