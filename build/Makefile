CPP=g++
CFLAGS=-Wall -O3 -g
VPATH=../src

OBJECTS= \
	Card.o \
	Pile.o

default: $(OBJECTS)
	$(CPP) -o ../mbj ../src/mbj.cpp \
		$(OBJECTS) \
		$(CFLAGS)

%.o: %.cpp %.h
	$(CPP) -c $< -o $*.o $(CFLAGS)
