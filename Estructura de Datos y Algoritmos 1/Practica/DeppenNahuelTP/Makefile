#Make file para  funciones de listas
CC=gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g
BIN = main

#Archivos fuente
SOURCE = $(wildcard src/*.c)#copilar los .c
HEADERS = $(wildcard headers/*.h)
SOURCE_O =  $(patsubst %.c,%.o,$(SOURCES))

#Compilar el programa
all: $(SOURCE_O)
		$(CC) $(CFLAGS) $^ -o  $(BIN) $(SOURCE)

#Crear .o desde .c
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

#limpieza
clean:
	@rm main
	
	

