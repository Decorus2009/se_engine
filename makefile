CC = g++
CFLAGS = -c -std=c++11 #-Wall
OBJECTS = bin/main.o bin/prepositions_dictionary.o bin/yandex_requester.o \
		  bin/text_analyzer.o bin/logger.o
LIBS = -lcurl -lexpat

vpath %.cpp %.hpp src
vpath %.o bin

all: pre-build exe

bin/main.o: src/main.cpp src/yandex_requester.hpp src/prepositions_dictionary.hpp src/logger.hpp
	$(CC) $(CFLAGS) $< -o $@

bin/text_analyzer.o: src/text_analyzer.cpp src/text_analyzer.hpp
	$(CC) $(CFLAGS) $< -o $@

bin/prepositions_dictionary.o: src/prepositions_dictionary.cpp src/prepositions_dictionary.hpp
	$(CC) $(CFLAGS) $< -o $@

bin/yandex_requester.o: src/yandex_requester.cpp src/yandex_requester.hpp
	$(CC) $(CFLAGS) $< -o $@

bin/logger.o: src/logger.cpp src/logger.hpp
	$(CC) $(CFLAGS) $< -o $@

exe: $(OBJECTS)
	$(CC) $^ $(LIBS) -o $@

pre-build:
	mkdir -p bin

clean:
	rm -rf ./bin *.o exe
