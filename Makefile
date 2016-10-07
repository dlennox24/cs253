CFILES = main.cpp histogram.cpp image.cpp
HFILES = histogram.h image.h
OFILES = main.o histogram.o image.o

CC = g++
FLAGS = -I.
FLAGSDEV = -Wall -g
EXE = PA4
TARPATH = tars/

main: ${CFILES} ${HFILES}
	$(CC) $(FLAGS) ${CFILES} -o $(EXE)

dev:
	$(CC) $(FLAGS) $(FLAGSDEV) ${CFILES} -o $(EXE)

clean:
	rm -f *.o *~ $(EXE)

tar:
	tar -cvf $(TARPATH)$(EXE).tar ${CFILES} ${HFILES} Makefile
