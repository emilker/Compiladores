CC = g++
FLEX = flex

all: scanner

scanner: scanner.o main.o
	$(CC) scanner.o main.o -o $@ -lfl

scanner.o: scanner.cpp
	$(CC) -c $< -o $@

scanner.cpp: scanner.flex
	$(FLEX) -o $@ $<

main.o: main.cpp
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	$(RM) scanner scanner.cpp *.o