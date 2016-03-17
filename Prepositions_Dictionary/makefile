CC=g++
CFLAGS= -c -Wall

all: exec

main.o: main.cpp Prepositions_Dictionary.h
	$(CC) $(CFLAGS) main.cpp

Prepositions_Dictionary.o : Prepositions_Dictionary.cpp Prepositions_Dictionary.h
	$(CC) $(CFLAGS) Prepositions_Dictionary.cpp

exec: main.o Prepositions_Dictionary.o
	$(CC) main.o Prepositions_Dictionary.o -o exec
	
clean:
	rm -rf *.o exec
