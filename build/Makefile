CPP=g++
CFLAGS=-Wall -O3 -g
VPATH=../src

OBJECTS=     \
	mbj_Card.o \
	mbj_Pile.o

default: $(OBJECTS)
	$(CPP) -o ../mbj ../src/mbj.cpp \
		$(OBJECTS) \
		$(CFLAGS)

%.o: %.cpp %.h
	$(CPP) -c $< -o $*.o $(CFLAGS)
