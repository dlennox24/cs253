CFILES = main.cpp histogram.cpp
HFILES = histogram.h
OFILES = main.o histogram.o

CC = g++
INC = -Wall -I.
EXE = PA3

main: ${CFILES} ${HFILES}
	$(CC) $(INC) ${CFILES} -o $(EXE)

clean:
	rm -f *.o *~ $(EXE)

tar:
	tar -cvf $(EXE).tar ${CFILES} ${HFILES} Makefile
