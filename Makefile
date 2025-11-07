CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wpedantic -Werror

all: main

clean:
	rm -f *.o main

test: test.o EventFactory.o EventManager.o StringFunctions.o
	$(CXX) $(CXXFLAGS) test.o EventFactory.o EventManager.o StringFunctions.o -o test

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

main: main.o EventFactory.o EventManager.o StringFunctions.o
	$(CXX) $(CXXFLAGS) main.o EventFactory.o EventManager.o StringFunctions.o -o main

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp

EventFactory.o: EventFactory.cpp EventFactory.h Event.h
	$(CXX) $(CXXFLAGS) -c EventFactory.cpp

EventManager.o: EventManager.cpp EventManager.h Event.h
	$(CXX) $(CXXFLAGS) -c EventManager.cpp

StringFunctions.o: StringFunctions.cpp StringFunctions.h
	$(CXX) $(CXXFLAGS) -c StringFunctions.cpp
