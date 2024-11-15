#ifndef NODO_H
#define NODO_H
#include "hash.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct entrada {
    char* clave;
    void* valor;
} entrada_t;

typedef struct nodo {
    entrada_t *entrada;
    struct nodo* sig;
    struct nodo* ant;
} nodo_t;

typedef void (*fndest_t)(void*);

entrada_t* entrada_crear(char* clave, void* valor);

nodo_t *nodo_crear(char* clave, void* valor);

void nodo_destruir(nodo_t *nodo, fndest_t destructor);

void nodos_destruir(nodo_t *nodo, fndest_t destructor);

bool nodos_insertar(nodo_t *nodo, char* clave, void* valor);

void* nodo_remover(nodo_t *nodo, char* clave);

nodo_t* nodo_buscar(nodo_t *nodo, char* clave);

#endif /* NODO_H */
