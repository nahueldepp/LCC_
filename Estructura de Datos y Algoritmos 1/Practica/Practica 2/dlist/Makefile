all: main
	

main: main.o dlist.o
	gcc -o main main.o dlist.o
	./main
main.o: main.c 
	gcc -c main.c dlist.h
dlist.o: dlist.c dlist.h
	gcc -c dlist.c 

clean: 
	rm -f dlist *.o