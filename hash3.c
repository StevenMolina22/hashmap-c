#include "src/hash.h"
#include <stdlib.h>
#include <string.h>
#include "src/lista.h"
#include "src/vec.h"

typedef struct nodo {
    char* clave;
    void* valor;
} entrada_t;

struct hash {
    vec_t* bucket; // vec_t<lista_t<entrada_t>>
    size_t size;
    size_t cap;
};

size_t hasher(const char *str)
{
    size_t idx = 5381;
    size_t c;

    while ((c = (size_t)*str++)) {
        idx = ((idx << 5) + idx) + c; // hash * 33 + c
    }
    return idx;
}

void destructor(void* elem)
{
    lista_destruir((lista_t*)elem);
    return;
}

int cmp_clave(void* _a, void* _b)
{
    entrada_t* a = _a;
    entrada_t* b = _b;
    return strcmp(a->clave, b->clave);
}

entrada_t* nodo_crear(char* clave, void* valor) {
    entrada_t* entrada = malloc(sizeof(entrada_t));
    if (!entrada)
        return NULL;
    entrada->clave = clave;
    entrada->valor = valor;
    return entrada;
}

entrada_t* encontrar_entrada(hash_t* hash, char* clave, cmp_t cmp)
{
    size_t idx = (hasher(clave) % hash->cap);
    lista_t* bucket = vec_obtener(hash->bucket, idx);

    entrada_t* entrada = lista_buscar(bucket, clave, cmp);
    return entrada;
}

vec_t* buckets_crear(hash_t* hash, size_t cap) {
    vec_t* buckets = vec_crear(cap, sizeof(lista_t*), &destructor);
    for (size_t i = 0; i < cap; i++) {
        lista_t* bucket = lista_crear();
        vec_asignar(buckets, i, bucket);
    }
    return buckets;
}

hash_t* hash_crear(size_t cap) {
    hash_t* hash = malloc(sizeof(hash_t));
    if (!hash)
        return NULL;
    hash->bucket = buckets_crear(hash, cap);
    hash->size = 0;
    hash->cap = cap;
    return hash;
}

size_t hash_cantidad(hash_t* hash) {
    return hash->size;
}

bool hash_rehash(hash_t* hash) {
    hash->cap *= 2;
    vec_t* old_buckets = hash->bucket;
    hash->bucket = buckets_crear(hash, hash->cap);
    for (size_t i = 0; i < vec_cantidad(old_buckets); i++) {
        lista_t* old_bucket = vec_obtener(old_buckets, i);
        l_iterador_t* it = l_iterador_crear(old_bucket);

        while (l_iterador_hay_siguiente(it)) {
            entrada_t* entrada = l_iterador_actual(it);
            size_t idx = hasher(entrada->clave);
            lista_t* bucket = vec_obtener(old_buckets, idx);
            lista_agregar_final(bucket, entrada);
            l_iterador_avanzar(it);
        }
        l_iterador_destruir(it);
    }
    return true;
}

bool hash_insertar(hash_t* hash, char* _clave, void* valor, void** encontrado) {
    if (!hash || !_clave)
        return false;
    char* clave = malloc(strlen(_clave) + 1);
    if (!clave)
        return false;
    strcpy(clave, _clave);
    size_t idx = hasher(clave) % hash->cap;

    entrada_t* entrada = encontrar_entrada(hash, clave, &cmp_clave);
    if (entrada) {
        if (encontrado)
            *encontrado = entrada->valor;
        entrada->valor = valor;
        return true;
    }
    lista_t* bucket = vec_obtener(hash->bucket, idx);
    entrada = nodo_crear(clave, valor);
    if (!entrada)
        return false;
    lista_agregar_final(bucket, entrada);
    hash->size++;
    return true;
}

void* hash_buscar(hash_t* hash, char* clave) {
    if (!hash || !clave)
        return NULL;
    entrada_t* entrada = encontrar_entrada(hash, clave, &cmp_clave);
    if (!entrada)
        return NULL;
    return entrada->valor;
}

bool hash_contiene(hash_t* hash, char* clave) {
    return encontrar_entrada(hash, clave, &cmp_clave) != NULL;
}

void* hash_quitar(hash_t* hash, char* clave) {
    size_t idx = hasher(clave) % hash->cap;
    lista_t* bucket = vec_obtener(hash->bucket, idx);
    size_t elem_idx = lista_encontrar_idx(bucket, clave, cmp_clave);
    return lista_remover(bucket, elem_idx);
}

size_t hash_iterar(hash_t* hash, bool (*f)(char*, void*, void*), void* ctx) {
    return 0;
}

void hash_destruir(hash_t* hash) {
    return;
}

void hash_destruir_todo(hash_t* hash, void (*destructor)(void*)) {
    return;
}
