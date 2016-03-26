CC = g++
CFLAGS = -c -std=c++11 -Wall
OBJECTS = main.o prepositions_dictionary.o yandex_requester.o request_sender.o xml_parser.o text_analyzer.o
LIBS = -lcurl -lexpat

vpath %.cpp %.hpp src
vpath %.o bin

all: exec

bin/main.o: src/main.cpp src/yandex_requester.hpp src/prepositions_dictionary.hpp
	$(CC) $(CFLAGS) $< -o $@

bin/text_analyzer.o: src/text_analyzer.cpp src/text_analyzer.hpp
	$(CC) $(CFLAGS) $< -o $@

bin/prepositions_dictionary.o: src/prepositions_dictionary.cpp src/prepositions_dictionary.hpp
	$(CC) $(CFLAGS) $< -o $@

bin/yandex_requester.o: src/yandex_requester.cpp src/request_sender.hpp src/xml_parser.hpp
	$(CC) $(CFLAGS) $< -o $@

bin/request_sender.o: src/request_sender.cpp src/request_sender.hpp
	$(CC) $(CFLAGS) $< -o $@

bin/xml_parser.o: src/xml_parser.cpp src/xml_parser.hpp
	$(CC) $(CFLAGS) $< -o $@

exec: $(OBJECTS)
	$(CC) $^ $(LIBS) -o $@

clean:
	rm -rf bin/*.o src/*.gch exec
