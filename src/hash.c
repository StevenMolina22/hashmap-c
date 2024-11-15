#include "hash.h"
#include <stdlib.h>
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

struct hash {
    nodo_t** tabla;
    size_t size;
    size_t cap;
};

static size_t hasher(const char *str)
{
    size_t idx = 5381;
    size_t c;

    while ((c = (size_t)*str++)) {
        idx = ((idx << 5) + idx) + c; // hash * 33 + c
    }
    return idx;
}

static nodo_t* nodo_crear(char* clave, void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    entrada_t* entrada = malloc(sizeof(entrada_t));
    if (!nodo || !entrada)
        return NULL;
    entrada->clave = clave;
    entrada->valor = valor;
    nodo->entrada = entrada;
    nodo->sig = NULL;
    nodo->ant = NULL;
    return nodo;
}

static void nodo_destruir(nodo_t* nodo) {
    free(nodo->entrada->clave);
    free(nodo->entrada);
    free(nodo);
}

static nodo_t* encontrar_entrada(hash_t* hash, char* clave)
{
    size_t idx = hasher(clave) % hash->cap;
    nodo_t* actual = hash->tabla[idx];
    while (actual) {
        if (strcmp(actual->entrada->clave, clave) == 0) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL;
}

static bool agregar_entrada(hash_t* hash, char* clave, void* valor) {
    size_t idx = hasher(clave) % hash->cap;
    nodo_t* nuevo = nodo_crear(clave, valor);
    if (!nuevo)
        return false;
    nodo_t* nodo = hash->tabla[idx];
    if (nodo) {
        nuevo->sig = nodo;
        nodo->ant = nuevo;
    }
    hash->tabla[idx] = nuevo;
    return true;
}

static bool hash_rehash(hash_t* hash) {
    hash->cap *= 2;
    nodo_t** tabla_vieja = hash->tabla;
    size_t size_viejo = hash->size;
    hash->size = 0;
    for (size_t i = 0; i < size_viejo; i++) {
        nodo_t* nodo = tabla_vieja[i];
        while (nodo) {
            if (!agregar_entrada(hash, nodo->entrada->clave, nodo->entrada->valor))
                return false;
            nodo = nodo->sig;
        }
    }
    return true;
}

hash_t* hash_crear(size_t cap) {
    hash_t* hash = malloc(sizeof(hash_t));
    nodo_t** tabla = calloc(cap, sizeof(nodo_t*));
    if (!hash || !tabla)
        return NULL;
    hash->tabla = tabla;
    hash->size = 0;
    hash->cap = cap;
    return hash;
}

size_t hash_cantidad(hash_t* hash) {
    return hash->size;
}

bool hash_insertar(hash_t* hash, char* _clave, void* valor, void** encontrado) {
    if (!hash || !_clave)
        return false;
    char* clave = malloc(strlen(_clave) + 1);
    if (!clave)
        return false;
    strcpy(clave, _clave);

    size_t idx = hasher(clave) % hash->cap;
    if ((float)hash->size / (float)hash->cap > 0.75) {
        hash_rehash(hash);
    }

    nodo_t* nodo = encontrar_entrada(hash, clave);
    if (nodo) {
        if (encontrado)
            *encontrado = nodo->entrada->valor;
        nodo->entrada->valor = valor;
        return true;
    }
    nodo = hash->tabla[idx];
    if (!agregar_entrada(hash, clave, valor))
        return false;
    hash->size++;
    return true;
}

void* hash_buscar(hash_t* hash, char* clave) {
    if (!hash || !clave)
        return NULL;
    nodo_t* nodo = encontrar_entrada(hash, clave);
    if (!nodo)
        return NULL;
    return nodo->entrada->valor;
}

bool hash_contiene(hash_t* hash, char* clave) {
    return encontrar_entrada(hash, clave) != NULL;
}

void* hash_quitar(hash_t* hash, char* clave) {
    size_t idx = hasher(clave) % hash->cap;
    nodo_t* nodo = encontrar_entrada(hash, clave);
    if (!nodo)
        return NULL;
    if (nodo->ant) {
        nodo->ant->sig = nodo->sig;
    } else {
        hash->tabla[idx] = nodo->sig;
    }
    if (nodo->sig) {
        nodo->sig->ant = nodo->ant;
    }
    void* valor = nodo->entrada->valor;
    nodo_destruir(nodo);
    hash->size--;
    return valor;
}

size_t hash_iterar(hash_t* hash, bool (*f)(char*, void*, void*), void* ctx) {
    size_t iterados = 0;
    for (size_t i = 0; i < hash->cap; i++) {
        nodo_t* actual = hash->tabla[i];
        while (actual) {
            if (!f(actual->entrada->clave, actual->entrada->valor, ctx)) {
                return iterados;
            }
            iterados++;
            actual = actual->sig;
        }
    }
    return iterados;
}

void hash_destruir(hash_t* hash) {
    hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t* hash, void (*destructor)(void*)) {
    if (!hash)
        return;
    for (size_t i = 0; i < hash->cap; i++) {
        nodo_t* actual = hash->tabla[i];
        while (actual) {
            nodo_t* siguiente = actual->sig;
            if (destructor)
                destructor(actual->entrada->valor);
            nodo_destruir(actual);
            actual = siguiente;
        }
    }
    free(hash->tabla);
    free(hash);
}
