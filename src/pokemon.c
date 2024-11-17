#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pokemon.h"
/*
    NOTA: Las funciones toman void* para poder ser utilizadas con hash_t
    😢
*/

int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = _p1;
	struct pokemon *p2 = _p2;
	return strcmp(p1->nombre, p2->nombre);
}

void liberar_pokemon(void *pokemon)
{
	struct pokemon *p = (struct pokemon *)pokemon;
	if (p) {
		free(p->nombre);
		free(p);
	}
}

bool print_pokemon(char *poke_name, void *pokemon, void *ctx)
{
	struct pokemon *p = (struct pokemon *)pokemon;
	if (p) {
		printf("Pokemon: %s\n", p->nombre);
		printf("  Tipo: %c\n", p->tipo);
		printf("  Fuerza: %d\n", p->fuerza);
		printf("  Destreza: %d\n", p->destreza);
		printf("  Resistencia: %d\n\n", p->resistencia);
	}
	return true;
}

// ----- Pokemon con archivos -----
struct pokemon *leer_pokemon(struct archivo_csv *archivo)
{
	bool (*funciones[N_COLUMNAS])(const char *, void *) = {
		read_string, read_char, read_int, read_int, read_int
	};

	char tipo;
	int fuerza, destreza, resistencia;
	char *nombre = NULL;
	void *punteros[N_COLUMNAS] = { &nombre, &tipo, &fuerza, &destreza,
				       &resistencia };

	// Lee una línea del CSV
	if (leer_linea_csv(archivo, N_COLUMNAS, funciones, punteros) !=
	    N_COLUMNAS) {
		free(nombre); // Libera en caso de fallo
		return NULL;
	}

	// Crea un nuevo Pokémon
	struct pokemon *pokemon = malloc(sizeof(struct pokemon));
	if (!pokemon) {
		free(nombre);
		return false;
	}
	*pokemon = (struct pokemon){ .nombre = nombre,
				     .tipo = tipo,
				     .fuerza = fuerza,
				     .destreza = destreza,
				     .resistencia = resistencia };

	return pokemon;
}

bool agregar_pokemones(struct archivo_csv *archivo, hash_t *pokedex)
{
	struct pokemon *pokemon;

	// Lee cada Pokémon y lo agrega a la lista
	while ((pokemon = leer_pokemon(archivo)) != NULL) {
		if (!hash_insertar(pokedex, pokemon->nombre, pokemon, NULL)) {
			liberar_pokemon(
				pokemon); // Libera si no se puede agregar
			return false;
		}
	}

	return true;
}

// ----- Pokemon input usuario -----
void buscar_pokemon(hash_t *pokedex)
{
	char nombre[100];
	printf("Ingresar nombre del pokemon: ");
	if (scanf("%99s", nombre) != 1) {
		printf("Nombre invalido\n");
		return;
	}

	struct pokemon buscado = { .nombre = nombre };
	struct pokemon *encontrado = hash_buscar(pokedex, buscado.nombre);
	if (encontrado) {
		print_pokemon(encontrado->nombre, encontrado, NULL);
	} else {
		printf("Pokemon no encontrado\n");
	}
}
