#ifndef POKEMON_H
#define POKEMON_H

#include <stdbool.h>
#include "utils.h"
#include "csv.h"
#include "hash.h"

#define ERROR -1
#define DELIMITADOR ';'
#define N_COLUMNAS 5

typedef struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
} Pokemon;

struct pokemon *leer_pokemon(struct archivo_csv *archivo);
bool agregar_pokemones(struct archivo_csv *archivo, hash_t *pokedex);
void liberar_pokemon(void *pokemon);
int comparar_nombre_pokemon(void *pokemon1, void *pokemon2);
bool print_pokemon(char *pokemon_name, void *pokemon, void *ctx);
void buscar_pokemon(hash_t *pokedex);

#endif // POKEMON_H
