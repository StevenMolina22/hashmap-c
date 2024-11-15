VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CC = gcc
DEBUG_FLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g

all: clean valgrind-alumno

valgrind-alumno: pruebas_alumno
	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

pruebas_alumno: src/*.c pruebas_alumno.c
	$(CC) $(CFLAGS) src/*.c pruebas_alumno.c -o pruebas_alumno

pruebas_vec: src/*.c pruebas_vec.c
	$(CC) $(CFLAGS) src/*.c pruebas_vec.c -o pruebas_vec

pruebas_lista: src/*.c pruebas_lista.c
	$(CC) $(CFLAGS) src/*.c pruebas_lista.c -o pruebas_lista

test: pruebas_alumno
	# ./pruebas_vec
	# ./pruebas_lista
	./pruebas_alumno
	rm -f pruebas_alumno

debug_pruebas: pruebas_alumno
	gdb ./pruebas_alumno

valgrind-ejemplo: ejemplo
	valgrind $(VALGRIND_FLAGS) ./ejemplo

ejemplo: src/*.c ejemplo.c
	$(CC) $(CFLAGS) src/*.c ejemplo.c -o ejemplo

clean:
	rm -f pruebas_alumno ejemplo
