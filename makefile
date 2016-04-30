CC = g++
CFLAGS = -g -c -std=c++11 #-Wall
OBJECTS = bin/prepositions_dictionary.o bin/yandex_requester.o \
		  bin/text_analyzer.o bin/logger.o
LIBS = -lcurl -lexpat

CFLAGS_TEST = -I /usr/gtest/include
OBJECTS_TEST = bin/text_analyzer_unittest.o
LIBS_TEST = -lgtest -lpthread -lgtest_main

#vpath %.cpp %.hpp src
#vpath %.o bin

all: pre-build exe

test: pre-build test_exe

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

bin/test_main.o: test_src/test_main.cpp
	$(CC) $(CFLAGS) $(CFLAGS_TEST) $< -o $@

bin/text_analyzer_unittest.o: test_src/text_analyzer_unittest.cpp src/text_analyzer.hpp
	$(CC) $(CFLAGS) $(CFLAGS_TEST) $< -o $@


exe: $(OBJECTS) bin/main.o
	$(CC) $^ $(LIBS) -o $@

test_exe: $(OBJECTS) $(OBJECTS_TEST) bin/test_main.o
	$(CC) $^ $(LIBS) $(LIBS_TEST) -o $@


pre-build:
	mkdir -p bin

clean:
	rm -rf ./bin *.o exe test_exe
