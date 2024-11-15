#include "lista.h"
#include <stdio.h>

typedef struct nodo {
	void *data;
	struct nodo *siguiente;
	struct nodo *anterior;
} nodo_t;

struct lista {
	size_t cant;
	nodo_t *frente;
	nodo_t *fondo;
};

struct l_iterador {
	nodo_t *actual;
};

typedef bool (*fn_t)(void* elem, void* ctx);

// ----- FUNCIONES AUXILIARES
nodo_t *nodo_crear(void *data)
{
	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (!nodo)
		return NULL;
	nodo->data = data;
	return nodo;
}
nodo_t *nodo_obtener(lista_t *lista, size_t idx)
{
	nodo_t *nodo = lista->frente;
	for (size_t i = 0; i < idx; i++) {
		nodo = nodo->siguiente;
	}
	return nodo;
}

nodo_t *nodo_buscar(lista_t *lista, void *data, cmp_t cmp) {
	if (!lista || !cmp)
		return NULL;
	nodo_t *nodo = lista->frente;
	while (nodo != NULL) {
		if (cmp(data, nodo->data) == 0)
			return nodo;
		nodo = nodo->siguiente;
	}
	return NULL;
}

lista_t *lista_crear()
{
	lista_t *lista = calloc(1, sizeof(lista_t));
	return lista;
}

void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista, NULL);
}

void lista_destruir_todo(lista_t *lista, void (*destructor)(void *))
{
	if (!lista)
		return;
	nodo_t *nodo = lista->frente;
	while (nodo != NULL) {
		if (destructor)
			destructor(nodo->data);
		nodo_t *temp = nodo;
		nodo = nodo->siguiente;
		free(temp);
	}
	free(lista);
}

size_t lista_cantidad(lista_t *lista)
{
	if (!lista)
		return 0;
	return lista->cant;
}

void insertar_frente(lista_t *lista, nodo_t *nuevo)
{
	nuevo->siguiente = lista->frente;
	nuevo->anterior = NULL;
	if (lista->frente)
		lista->frente->anterior = nuevo;
	lista->frente = nuevo;
	if (!lista->fondo)
		lista->fondo = nuevo;
}

void insertar_medio(nodo_t *nodo, nodo_t *nuevo)
{
	nuevo->siguiente = nodo->siguiente;
	nuevo->anterior = nodo;
	if (nodo->siguiente)
		nodo->siguiente->anterior = nuevo;
	nodo->siguiente = nuevo;
}

bool lista_insertar(lista_t *lista, size_t idx, void *data)
{
	if (!lista || idx > lista->cant)
		return false;
	if (idx == lista->cant)
		return lista_agregar_final(lista, data);

	nodo_t *nuevo = nodo_crear(data);
	if (!nuevo)
		return false;
	if (idx == 0) {
		insertar_frente(lista, nuevo);
	} else {
		nodo_t *nodo = nodo_obtener(lista, idx - 1);
		insertar_medio(nodo, nuevo);
	}
	lista->cant++;
	return true;
}

bool lista_agregar_final(lista_t *lista, void *elem)
{
	if (!lista)
		return false;
	nodo_t *nuevo = nodo_crear(elem);
	if (!nuevo)
		return false;
	nuevo->siguiente = NULL;
	nuevo->anterior = lista->fondo;

	if (!lista->frente) {
		lista->frente = nuevo;
		lista->fondo = nuevo;
	} else {
		lista->fondo->siguiente = nuevo;
		lista->fondo = nuevo;
	}

	lista->cant++;
	return true;
}

void* remover_nodo(lista_t *lista, nodo_t *nodo)
{
    void* data = nodo->data;
	if (nodo->anterior)
		nodo->anterior->siguiente = nodo->siguiente;
	if (nodo->siguiente)
		nodo->siguiente->anterior = nodo->anterior;
	if (nodo == lista->frente)
		lista->frente = nodo->siguiente;
	if (nodo == lista->fondo)
		lista->fondo = nodo->anterior;
	free(nodo);
	lista->cant--;
	return data;
}

void* lista_remover(lista_t *lista, size_t idx)
{
	if (!lista || idx >= lista->cant)
		return false;

	nodo_t *nodo;
	if (idx == 0) {
		nodo = lista->frente;
	} else if (idx == lista->cant - 1) {
		nodo = lista->fondo;
	} else {
		nodo = nodo_obtener(lista, idx);
		if (!nodo)
		    return NULL;
	}
	return remover_nodo(lista, nodo);
}

bool lista_eliminar_valor(lista_t* lista, void* data, cmp_t cmp) {
 //    nodo_t* buscado = nodo_buscar(lista, data, cmp);
	// if (!buscado)
	//    return NULL;
    return NULL;
}

size_t lista_encontrar_idx(lista_t* lista, void* data, cmp_t cmp) {
    nodo_t* nodo = lista->frente;
    size_t i = 0;
    while (nodo) {
        if (cmp(data, nodo->data) == 0) {
            return i;
        }
        nodo = nodo->siguiente;
        i++;
    }
    return i;
}

void *lista_buscar(lista_t *lista, void *data, cmp_t cmp) {
	if (!lista || !cmp)
		return NULL;
	nodo_t* buscado = nodo_buscar(lista, data, cmp);
	if (!buscado)
	   return NULL;
	return buscado->data;
}

void* lista_obtener(lista_t *lista, size_t idx)
{
	if (!lista || idx >= lista->cant)
		return false;

	nodo_t* nodo = nodo_obtener(lista, idx);
	if (!nodo)
	   return NULL;
	return nodo->data;
}

size_t lista_iterar(lista_t *lista, fn_t fn, void *ctx)
{
	if (!lista || !fn)
		return 0;

	nodo_t *actual = lista->frente;
	size_t i = 0;
	for (i = 0; actual != NULL; i++) {
		if (!fn(actual->data, ctx))
			return ++i;
		actual = actual->siguiente;
	}
	return i;
}

l_iterador_t *l_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;
	l_iterador_t *iter = malloc(sizeof(l_iterador_t));
	if (!iter)
		return NULL;

	iter->actual = lista->frente;
	return iter;
}

bool l_iterador_hay_siguiente(l_iterador_t *it)
{
	if (!it || !it->actual)
		return false;
	return true;
}

void l_iterador_avanzar(l_iterador_t *it)
{
	if (!it || !it->actual)
		return;
	it->actual = it->actual->siguiente;
}

void *l_iterador_actual(l_iterador_t *it)
{
	if (!it || !it->actual)
		return NULL;
	return it->actual->data;
}

void l_iterador_destruir(l_iterador_t *it)
{
	if (it)
		free(it);
}
