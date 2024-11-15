// #include "vec.h"

// struct vec {
//     entrada_t* arr;
//     size_t cant;
//     size_t cap;
// };

// struct v_iter {
//     vec_t* vec;
//     size_t idx;
// };
void jeje() {

}

// vec_t* vec_crear(size_t cap, size_t elem_size, func_t destructor) {
//     vec_t* v = malloc(sizeof(vec_t));
//     if (!v)
//         return NULL;
//     v->arr = calloc(cap, sizeof(void*));
//     if (!v->arr) {
//         free(v);
//         return NULL;
//     }
//     v->cap = cap;
//     v->cant = 0;
//     v->elem_size = elem_size;
//     v->destructor = destructor;
//     return v;
// }

// void vec_destruir(vec_t* v) {
//     if (!v)
//         return;
//     for (size_t i = 0; i < v->cant; i++) {
//         if (v->destructor)
//             v->destructor(v->arr[i]);
//     }
//     free(v->arr);
//     free(v);
// }

// bool vec_redimensionar(vec_t* v, size_t cap) {
//     void* temp = realloc(v->arr, cap * sizeof(void*));
//     if (!temp)
//         return false;
//     v->arr = temp;
//     v->cap = cap;
//     return true;
// }

// bool vec_insertar(vec_t* v, void* elem) {
//     if (!v)
//         return false;
//     if (v->cant >= v->cap) {
//         if (!vec_redimensionar(v, 2 * v->cap))
//             return false;
//     }
//     v->arr[v->cant] = elem;
//     v->cant++;
//     return true;
// }

// void vec_eliminar(vec_t* v, size_t idx) {
//     if (!v || idx >= v->cant)
//         return;
//     if (v->destructor)
//         v->destructor(v->arr[idx]);
//     for (size_t i = idx; i < v->cant-1; i++) {
//         v->arr[i] = v->arr[i+1];
//     }
//     v->cant--;
// }

// void* vec_obtener(vec_t* v, size_t idx) {
//     if (!v || idx >= v->cant)
//         return NULL;
//     return v->arr[idx];
// }

// bool vec_asignar(vec_t* v, size_t idx, void* elem) {
//     if (!v || idx >= v->cant)
//         return false;
//     if (v->destructor)
//         v->destructor(v->arr[idx]);
//     v->arr[idx] = elem;
//     return true;
// }

// size_t vec_cantidad(vec_t* v) {
//     if (!v)
//         return 0;
//     return v->cant;
// }

// size_t vec_capacidad(vec_t* v) {
//     if (!v)
//         return 0;
//     return v->cap;
// }

// size_t vec_foreach(vec_t* v, fn_t f, void* ctx) {
//     if (!v || !f)
//         return 0;
//     for(size_t i = 0; i < v->cant; i++) {
//         if (!f(v->arr[i], ctx))
//             return i + 1;
//     }
//     return 0;
// }

// // ITERADOR
// v_iter_t* v_iter_crear(vec_t* v) {
//     v_iter_t* it = malloc(sizeof(v_iter_t));
//     if (!it)
//         return NULL;
//     it->vec = v;
//     it->idx = 0;
//     return it;
// }

// bool v_iter_hay_siguiente(v_iter_t* it) {
//     if (!it)
//         return false;
//     return (it->idx) < (it->vec->cant);
// }

// size_t v_iter_siguiente(v_iter_t* it, void** elem) {
//     *elem = it->vec->arr[it->idx];
//     return it->idx++;
// }

// void v_iter_destruir(v_iter_t *it)
// {
//     free(it);
// }
