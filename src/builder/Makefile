CC=gcc
CFLAGS=-c -Wall -Werror -pedantic
LIB=-lm

all: clean builder.o
	$(CC) $(LIB) -o builder.out builder.o
builder.o: builder.c
	$(CC) $(CFLAGS) builder.c
clean:
	rm -f *.o *~ *.out
