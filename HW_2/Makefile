default: all

all: clean prog b2s

dynArray.o: dynArray.c dynArray.h 
	gcc -Wall -ansi -c dynArray.c	

prog: stackapp.c dynArray.o
	gcc -Wall -ansi -o prog dynArray.o stackapp.c

b2s: dynArray.o
	gcc -Wall -ansi -o b2s dynArray.o bag2set.c
		
clean:
	rm -f *.o
	rm -f prog
	rm -f b2s