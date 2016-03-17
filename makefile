CC=g++
CFLAGS= -c -g -Wall

all: exec

main.o: main.cpp Yandex_requester.h
	$(CC) $(CFLAGS) main.cpp

Yandex_requester.o : Yandex_requester.cpp req_sender.h xml_parser.h
	$(CC) $(CFLAGS) Yandex_requester.cpp

req_sender.o: req_sender.cpp req_sender.h
	$(CC) $(CFLAGS) req_sender.cpp

xml_parser.o: xml_parser.cpp xml_parser.h
	$(CC) $(CFLAGS) xml_parser.cpp

exec: main.o Yandex_requester.o req_sender.o xml_parser.o
	$(CC) main.o Yandex_requester.o req_sender.o xml_parser.o -lcurl -lexpat -o exec
	
clean:
	rm -rf *.o exec
