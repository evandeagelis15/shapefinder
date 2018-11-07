CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic

all: 
	$(CXX) -o main main.cpp

clean:
	rm -f *.o
	rm main
