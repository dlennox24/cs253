MC = main.cpp
TC = test.cpp
CFILES = histogram.cpp image.cpp
HFILES = histogram.h image.h
OFILES = main.o histogram.o image.o

CC = g++
FLAGS = -I.
FLAGSDEV = -Wall -g
EXE = PA5
TARPATH = tars/

main: ${CFILES} ${HFILES}
	$(CC) $(FLAGS) $(MC) ${CFILES} -o $(EXE)

dev:
	$(CC) $(FLAGS) $(FLAGSDEV) $(MC) ${CFILES} -o $(EXE)

test:
	$(CC) $(FLAGS) $(FLAGSDEV) $(TC) ${CFILES} -o $(EXE)

clean:
	rm -f *.o *~ $(EXE)

tar:
	tar -cvf $(TARPATH)$(EXE).tar $(MC) ${CFILES} ${HFILES} Makefile
