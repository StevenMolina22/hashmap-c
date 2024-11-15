#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdbool.h>

typedef int (*cmp_t)(void *, void *);
typedef struct lista lista_t;
typedef struct l_iterador l_iterador_t;

lista_t *lista_crear();
void lista_destruir(lista_t *);

/**
 * Destruye la lista aplicando la funcion destructora (si no es NULL) a cada elemento.
 * */
void lista_destruir_todo(lista_t *l, void (*destructor)(void *));

/*
 * Devuelve la cantidad de elementos de la lista.
 * Una lista NULL tiene 0 elementos.
 */
size_t lista_cantidad(lista_t *l);

/**
 * Inserta un elemento en la lista en la posicion dada.
 *
 * Si la posición es mayor a la cantidad de elementos, es un error.
 *
 * Devuelve true si pudo, false en caso de error.
 *
 */
bool lista_insertar(lista_t *l, size_t idx, void *data);

/**
  * Inserta un elemento al final de la lista.
  */
bool lista_agregar_final(lista_t *l, void *data);

/**
 * Elimina un elemento de la posicion dada.
 *
 * El elemento quitado se guarda en elemento_quitado (si se puede quitar y si no es null).
 *
 * En caso de error devuelve false, caso contrario true.
 */
void* lista_remover(lista_t *l, size_t idx);

/**
 * Busca el elemento buscado en la lista y lo devuelve si lo encuentra.
 *
 * Para buscar el elemento, se aplica la función de comparacion.
 *
 * En caso de no encontrarlo devuelve NULL.
 */
void *lista_buscar(lista_t *l, void *buscado,
			    int (*comparador)(void *, void *));

/**
 * Obtiene el elemento almacenado en una posición
 *
 * Si la posicion es inválida es un error.
 *
 * El elemento encontrado se almacena en elemento_encontrado (a menos que sea NULL);
 *
 * Devuelve true si pudo obtener el elemento o false en caso de error.
 */
void* lista_obtener(lista_t *l, size_t idx);

size_t lista_encontrar_idx(lista_t* lista, void* data, cmp_t cmp);

/**
 * Recorre la lista aplicando la funcion f a cada elemento en orden.
 *
 * ctx se le pasa como segundo parámetro a f.
 *
 * Si la funcion devuelve true se debe seguir iterando, caso contrario no.
 *
 * Devuelve la cantidad de elementos iterados.
 * */
size_t lista_iterar(lista_t *l, bool (*f)(void *, void *),
			      void *ctx);

/**
 * Crea un iterador externo para una lista
 *
 * En caso de error devuelve NULL
 */
l_iterador_t *l_iterador_crear(lista_t *l);

/**
 * Devuelve true si hay siguiente.
 */
bool l_iterador_hay_siguiente(l_iterador_t *);

/**
 *
 * Hace que el iterador avance al siguiente elemento de la lista.
 *
 */
void l_iterador_avanzar(l_iterador_t *);

/**
 * Devuelve el elemento iterado
 */
void *l_iterador_actual(l_iterador_t *);

/**
 * Eso
 */
void l_iterador_destruir(l_iterador_t *);

#endif /* LISTA_H */
