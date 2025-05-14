CXX = g++
FLEX = flex
BISON = bison -Wcounterexamples --defines=token.h

all: validator

validator: parser.o scanner.o main.o statement.o audiogenerator.o
	$(CXX) scanner.o parser.o main.o statement.o audiogenerator.o -o validator -lfluidsynth -lsndfile

parser.o: parser.cpp
	$(CXX) -c -I. parser.cpp

parser.cpp: parser.bison
	$(BISON) -v --output parser.cpp parser.bison

scanner.o: token.h scanner.cpp
	$(CXX) -c scanner.cpp

scanner.cpp: scanner.flex 
	$(FLEX) -o scanner.cpp scanner.flex

main.o: token.h main.cpp
	$(CXX) -c -I. main.cpp

statement.o: statement.hpp statement.cpp
	$(CXX) -c -I. statement.cpp	

audiogenerator.o: audiogenerator.hpp audiogenerator.cpp
	$(CXX) -c -I. audiogenerator.cpp	

.PHONY:
clean:
	$(RM) *.o parser.cpp parser.output token.h scanner.cpp validator Melodia.wav