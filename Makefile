CFILES = main.cpp histogram.cpp image.cpp
HFILES = histogram.h image.h
OFILES = main.o histogram.o image.o

CC = g++
INC = -Wall -I.
EXE = PA4

main: ${CFILES} ${HFILES}
	$(CC) $(INC) ${CFILES} -o $(EXE)

clean:
	rm -f *.o *~ $(EXE)

tar:
	tar -cvf $(EXE).tar ${CFILES} ${HFILES} Makefile
