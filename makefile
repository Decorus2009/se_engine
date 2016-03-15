CC=g++
CFLAGS= -c

all: exec

main.o: main.cpp xml_parser.h req_sender.h
	$(CC) $(CFLAGS) main.cpp

req_sender.o: req_sender.cpp req_sender.h
	$(CC) $(CFLAGS) req_sender.cpp

xml_parser.o: xml_parser.cpp xml_parser.h
	$(CC) $(CFLAGS) xml_parser.cpp

exec: main.o req_sender.o xml_parser.o
	$(CC) main.o req_sender.o xml_parser.o -lcurl -lexpat -o exec
	
clean:
	rm -rf *.o exec
