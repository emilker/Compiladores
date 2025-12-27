CXX = g++
FLEX = flex
BISON = bison -Wcounterexamples --defines=src/token.h

OBJDIR = bin
SRCDIR = src
INCDIR = include
GRAMDIR = grammar

OBJS = $(OBJDIR)/parser.o $(OBJDIR)/scanner.o $(OBJDIR)/main.o $(OBJDIR)/statement.o $(OBJDIR)/audiogenerator.o

all: RhythmCode

RhythmCode: $(OBJS)
	$(CXX) $(OBJS) -o $(OBJDIR)/RhythmCode -lfluidsynth -lsndfile

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/parser.o: $(SRCDIR)/parser.cpp | $(OBJDIR)
	$(CXX) -c -I$(INCDIR) $(SRCDIR)/parser.cpp -o $@

$(SRCDIR)/parser.cpp: $(GRAMDIR)/parser.bison
	$(BISON) -v --output=$(SRCDIR)/parser.cpp $(GRAMDIR)/parser.bison

$(OBJDIR)/scanner.o: $(SRCDIR)/token.h $(SRCDIR)/scanner.cpp | $(OBJDIR)
	$(CXX) -c -I$(INCDIR) $(SRCDIR)/scanner.cpp -o $@

$(SRCDIR)/scanner.cpp: $(GRAMDIR)/scanner.flex
	$(FLEX) -o $(SRCDIR)/scanner.cpp $(GRAMDIR)/scanner.flex

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp | $(OBJDIR)
	$(CXX) -c -I$(INCDIR) $(SRCDIR)/main.cpp -o $@

$(OBJDIR)/statement.o: $(INCDIR)/statement.hpp $(SRCDIR)/statement.cpp | $(OBJDIR)
	$(CXX) -c -I$(INCDIR) $(SRCDIR)/statement.cpp -o $@

$(OBJDIR)/audiogenerator.o: $(INCDIR)/audiogenerator.hpp $(SRCDIR)/audiogenerator.cpp | $(OBJDIR)
	$(CXX) -c -I$(INCDIR) $(SRCDIR)/audiogenerator.cpp -o $@

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) $(SRCDIR)/parser.cpp $(SRCDIR)/parser.output $(SRCDIR)/token.h $(SRCDIR)/scanner.cpp $(OBJDIR)/RhythmCode YourSongs/*.wav