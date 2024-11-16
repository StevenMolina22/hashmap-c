#ifndef TIPOS_H
#define TIPOS_H

#include <stdlib.h>
#include <string.h>

typedef struct entrada {
	char *clave;
	void *valor;
} entrada_t;

typedef struct nodo {
	entrada_t *entrada;
	struct nodo *sig;
	struct nodo *ant;
} nodo_t;

struct hash {
	nodo_t **tabla;
	size_t size;
	size_t cap;
};

size_t hasher(const char *str);
#endif
