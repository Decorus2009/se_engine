CC=g++
CFLAGS= -c

all: exec

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

se_engine.o: se_engine.cpp
	$(CC) $(CFLAGS) se_engine.cpp

xml_parser.o: xml_parser.cpp
	$(CC) $(CFLAGS) xml_parser.cpp

exec: main.o se_engine.o xml_parser.o
	$(CC) main.o se_engine.o xml_parser.o -lcurl -lexpat -o exec

clean:
	rm -rf *.o
