CC=gcc
CFLAGS=-lm -Wall -Werror -pedantic

all: clean builder.o 
	$(CC) -o builder builder.o $(CFLAGS)

clean:
	rm -f *.o *~ *.out core builder 

