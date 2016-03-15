CC=g++
CFLAGS= -c -g

all: exec

main.o: main.cpp req_sender.h
	$(CC) $(CFLAGS) main.cpp

req_sender.o: req_sender.cpp req_sender.h
	$(CC) $(CFLAGS) req_sender.cpp

exec: main.o req_sender.o 
	$(CC) main.o req_sender.o -lcurl -o exec

clean:
	rm *.o exec
