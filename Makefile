CXX = g++
FLEX = flex
BISON = bison -Wcounterexamples --defines=token.h

OBJDIR = bin
OBJS = $(OBJDIR)/parser.o $(OBJDIR)/scanner.o $(OBJDIR)/main.o $(OBJDIR)/statement.o $(OBJDIR)/audiogenerator.o

all: RhythmCode

RhythmCode: $(OBJS)
	$(CXX) $(OBJS) -o RhythmCode -lfluidsynth -lsndfile

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/parser.o: parser.cpp | $(OBJDIR)
	$(CXX) -c -I. parser.cpp -o $@

parser.cpp: parser.bison
	$(BISON) -v --output parser.cpp parser.bison

$(OBJDIR)/scanner.o: token.h scanner.cpp | $(OBJDIR)
	$(CXX) -c scanner.cpp -o $@

scanner.cpp: scanner.flex 
	$(FLEX) -o scanner.cpp scanner.flex

$(OBJDIR)/main.o: token.h main.cpp | $(OBJDIR)
	$(CXX) -c -I. main.cpp -o $@

$(OBJDIR)/statement.o: statement.hpp statement.cpp | $(OBJDIR)
	$(CXX) -c -I. statement.cpp -o $@

$(OBJDIR)/audiogenerator.o: audiogenerator.hpp audiogenerator.cpp | $(OBJDIR)
	$(CXX) -c -I. audiogenerator.cpp -o $@

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) parser.cpp parser.output token.h scanner.cpp RhythmCode YourSongs/*.wav
