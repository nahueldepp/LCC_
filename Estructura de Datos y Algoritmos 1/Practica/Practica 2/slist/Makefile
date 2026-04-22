all: main

main: main.o slist.o 
	gcc -s -g -o  main main.o slist.o 
	valgrind --tool=memcheck --leak-check=full ./main

main.o: main.c slist.h
	gcc -c main.c
slist.o: slist.c slist.h
	gcc -c slist.c 

clean: 
	rm -f slist *.o