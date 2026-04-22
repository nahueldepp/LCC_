#aplcaciones para arreglos unidimencionales
OBJS1 = main.o matriz_uni.o
#para el metodo de arreglos bidimencionales
OBJS2 = main.o matriz_bi.o
all: ejer5_bi ejer5_uni

#crea y ejecuta el archivo matriz_uni, donde se implementan funciones usando matrices de arreglos unidimensionales
ejer5_uni: $(OBJS1)
	gcc -o matriz_uni $(OBJS1)
	./matriz_uni
#crea y ejecuta el archivo matriz_uni, donde se implementan funciones usando matrices de arreglos bidimensionales
ejer5_bi: $(OBJS2)
	gcc -o matriz_bi $(OBJS2)
	./matriz_bi

#crea main.o (archivo preprocesado)
main.o: main.c matriz.h
	gcc -c main.c

matriz_uni.o: matriz_uni.c matriz.h
	gcc -c matriz_uni.c

matriz_bi.o: matriz_bi.c matriz.h
	gcc -c matriz_bi.c

clean: 
	rm -f ejer5 *.o