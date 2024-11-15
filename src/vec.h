#ifndef VEC_H
#define VEC_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct vec vec_t;
typedef struct v_iter v_iter_t;
typedef bool (*fn_t)(void* elem, void* ctx);
typedef void (*func_t) (void*);

/*
 * Destructor se usa para liberar memoria de elementos, si es NULL no se usa
*/
vec_t* vec_crear(size_t cap, size_t elem_size, func_t destructor);

void vec_destruir(vec_t*);

bool vec_insertar(vec_t* v, void* elem);

void vec_eliminar(vec_t* v, size_t idx);

void* vec_obtener(vec_t* v, size_t idx);

bool vec_asignar(vec_t* v, size_t idx, void* elem);

size_t vec_cantidad(vec_t* v);

size_t vec_capacidad(vec_t* v);

size_t vec_foreach(vec_t* v, fn_t f, void* ctx);

v_iter_t* v_iter_crear(vec_t* v);

bool v_iter_hay_siguiente(v_iter_t* it);

/*
Retorna: Indice del elemento siguiente (-1 si no hay)

Pre:
    - it es valido
    - hay siguiente
Post:
    - elem es asignado al elemento si elem no es null
*/
size_t v_iter_siguiente(v_iter_t* it, void** elem);
void v_iter_destruir(v_iter_t* it);

#endif
