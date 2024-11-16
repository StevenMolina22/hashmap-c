#include "src/hash.h"
#include "src/csv.h"
#include "src/pokemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1

int obtener_opcion_usuario(void)
{
	printf("1. Buscar pokemon\n");
	printf("2. Listar todos los pokemones\n");
	printf("Ingrese una opcion: ");

	int opcion;
	if (scanf("%d", &opcion) != 1) {
		printf("Opcion invalida\n");
		return ERROR;
	}
	return opcion;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Uso: %s <archivo.csv>\n", argv[0]);
		return ERROR;
	}

	struct archivo_csv *archivo = abrir_archivo_csv(argv[1], DELIMITADOR);
	if (!archivo) {
		printf("Archivo inexistente");
		return ERROR;
	}

	hash_t *pokedex = hash_crear(20);
	if (!pokedex) {
		printf("Error al crear el ABB\n");
		cerrar_archivo_csv(archivo);
		return ERROR;
	}

	if (!agregar_pokemones(archivo, pokedex)) {
		cerrar_archivo_csv(archivo);
		hash_destruir_todo(pokedex, liberar_pokemon);
		return ERROR;
	}
	cerrar_archivo_csv(archivo);

	int opcion = obtener_opcion_usuario();
	if (opcion == ERROR) {
		hash_destruir_todo(pokedex, liberar_pokemon);
		return ERROR;
	}

	switch (opcion) {
	case 1:
		buscar_pokemon(pokedex);
		break;
	case 2:
		hash_iterar(pokedex, print_pokemon, NULL);
		break;
	default:
		printf("Opcion invalida\n");
		hash_destruir_todo(pokedex, liberar_pokemon);
		return ERROR;
	}

	hash_destruir_todo(pokedex, liberar_pokemon);
	return 0;
}
