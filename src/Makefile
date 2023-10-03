PROGRAM = simulazione
OBJECTS = simulation.o alice.o bob.o reconciliation.o channel.o paramEstimation.o decoder.o main.o

CC = g++
CFLAGS = -O3 -Wall 

.SUFFIXES: .o .C

all: ${OBJECTS}
	${CC} -o ${PROGRAM} ${OBJECTS}

.C.o: $<
	$(CC) ${CFLAGS} -c $< -o $@

.PHONY: clean

clean: 
	rm -f simulazione *.csv *.o
