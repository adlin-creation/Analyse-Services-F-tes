OPTIONS=-O2
C11=-std=c++11

all : tp3

tp3 : tp3.cpp journal.o date.o
	g++ ${C11} ${OPTIONS} -o tp3 tp3.cpp journal.o date.o
	
date.o : date.cpp date.h
	g++ ${C11} ${OPTIONS} -c -o date.o date.cpp

journal.o : journal.cpp journal.h date.h arbreavl.h
	g++ ${C11} ${OPTIONS} -c -o journal.o journal.cpp

clean:
	rm -rf tp3 *~ *.o *.gch

