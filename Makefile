MC = main.cpp
TC = testMain.cpp
CFILES = histogram.cpp image.cpp data.cpp cluster.cpp
HFILES = histogram.h image.h data.h cluster.h

CC = g++
FLAGS = -I.
FLAGSDEV = -Wall -g
EXE = PA6
TARPATH = tars/

main: ${CFILES} ${HFILES}
	$(CC) $(FLAGS) $(MC) ${CFILES} -o $(EXE)

dev:
	$(CC) $(FLAGS) $(FLAGSDEV) $(MC) ${CFILES} -o $(EXE)

testMain:
	$(CC) $(FLAGS) $(FLAGSDEV) $(TC) ${CFILES} -o $(EXE)

clean:
	rm -f *.o *~ $(EXE)

tar:
	tar -cvf $(TARPATH)$(EXE).tar $(MC) ${CFILES} ${HFILES} Makefile
