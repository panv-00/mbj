CPP=g++
CFLAGS=-Wall -O3 -g
VPATH=../src

OBJECTS=              \
	Card.o              \
	Pile.o              \
	mbj_get_input.o     \
	mbj_format_number.o \
	lwnlib_screen.o     \
	mbj.o

default: $(OBJECTS)
	$(CPP) -o ../mbj ../src/main.cpp \
		$(OBJECTS) \
		$(CFLAGS)

%.o: %.cpp %.h
	$(CPP) -c $< -o $*.o $(CFLAGS)
