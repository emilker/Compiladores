CXX = g++
FLEX = flex
BISON = bison -Wcounterexamples --defines=token.h

all: validator

validator: parser.o scanner.o main.o ast_node_interface.o
	$(CXX) scanner.o parser.o main.o ast_node_interface.o -o validator

parser.o: parser.cpp
	$(CXX) -c -I. parser.cpp

parser.cpp: parser.bison
	$(BISON) -v --output parser.cpp parser.bison

scanner.o: token.h scanner.cpp
	$(CXX) -c scanner.cpp

scanner.cpp: scanner.flex
	$(FLEX) -o scanner.cpp scanner.flex

main.o: token.h main.cpp
	$(CXX) -c main.cpp

ast_node_interface.o: ast_node_interface.hpp ast_node_interface.cpp
	$(CXX) -c -I. ast_node_interface.cpp	

.PHONY:
clean:
	$(RM) *.o parser.cpp parser.output token.h scanner.cpp validator