#include "pa2m.h"
#include "src/vec.h"

void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i == j, "i es igual a j (%d == %d)", i, j);
	pa2m_afirmar(2*i == 10, "2*i es igual a 2 (%d)", 2*i);
}

void prueba_crear_vector() {
    pa2m_nuevo_grupo("Pruebas de creación de vector");

    vec_t* vec = vec_crear(10, sizeof(int), NULL);
    pa2m_afirmar(vec != NULL, "Se puede crear un vector con capacidad 10");
    pa2m_afirmar(vec_cantidad(vec) == 0, "La cantidad de elementos es 0");
    pa2m_afirmar(vec_capacidad(vec) == 10, "La capacidad del vector es 10");

    vec_destruir(vec);
}

void prueba_insertar_elemento() {
    pa2m_nuevo_grupo("Pruebas de inserción de elementos");

    vec_t* vec = vec_crear(10, sizeof(int), NULL);
    int elem = 5;
    bool result = vec_insertar(vec, &elem);
    pa2m_afirmar(result, "Se puede insertar un elemento en el vector");
    pa2m_afirmar(vec_cantidad(vec) == 1, "La cantidad de elementos es 1");

    int* obtained_elem = (int*)vec_obtener(vec, 0);
    pa2m_afirmar(obtained_elem != NULL, "Se puede obtener el elemento insertado");
    pa2m_afirmar(*obtained_elem == 5, "El elemento obtenido es correcto");

    vec_destruir(vec);
}

void prueba_eliminar_elemento() {
    pa2m_nuevo_grupo("Pruebas de eliminación de elementos");

    vec_t* vec = vec_crear(10, sizeof(int), NULL);
    int elem = 5;
    vec_insertar(vec, &elem);
    vec_eliminar(vec, 0);
    pa2m_afirmar(vec_cantidad(vec) == 0, "La cantidad de elementos es 0 después de eliminar");

    vec_destruir(vec);
}

void prueba_asignar_elemento() {
    pa2m_nuevo_grupo("Pruebas de asignación de elementos");

    vec_t* vec = vec_crear(10, sizeof(int), NULL);
    int elem = 5;
    vec_insertar(vec, &elem);
    int new_elem = 10;
    bool result = vec_asignar(vec, 0, &new_elem);
    pa2m_afirmar(result, "Se puede asignar un nuevo valor a un elemento existente");

    int* obtained_elem = (int*)vec_obtener(vec, 0);
    pa2m_afirmar(obtained_elem != NULL, "Se puede obtener el elemento asignado");
    pa2m_afirmar(*obtained_elem == 10, "El elemento asignado es correcto");

    vec_destruir(vec);
}

bool sum_fn(void* elem, void* ctx) {
    *(int*)ctx += *(int*)elem;
    return true;
}

void prueba_iterar_vector() {
    pa2m_nuevo_grupo("Pruebas de iteración de elementos");

    vec_t* vec = vec_crear(10, sizeof(int), NULL);
    int elem1 = 1, elem2 = 2, elem3 = 3;
    vec_insertar(vec, &elem1);
    vec_insertar(vec, &elem2);
    vec_insertar(vec, &elem3);

    size_t sum = 0;

    vec_foreach(vec, sum_fn, &sum);
    pa2m_afirmar(sum == 6, "La suma de los elementos es correcta");

    vec_destruir(vec);
}

void prueba_iterador() {
    pa2m_nuevo_grupo("Pruebas del iterador");

    vec_t* vec = vec_crear(10, sizeof(int), NULL);
    int elem1 = 1, elem2 = 2, elem3 = 3;
    vec_insertar(vec, &elem1);
    vec_insertar(vec, &elem2);
    vec_insertar(vec, &elem3);

    v_iter_t* iter = v_iter_crear(vec);
    pa2m_afirmar(iter != NULL, "Se puede crear un iterador para el vector");

    int* elem;
    size_t idx;

    pa2m_afirmar(v_iter_hay_siguiente(iter), "El iterador tiene un siguiente elemento");
    idx = v_iter_siguiente(iter, (void**)&elem);
    pa2m_afirmar(idx == 0, "El índice del primer elemento es 0");
    pa2m_afirmar(*elem == 1, "El primer elemento es correcto");

    pa2m_afirmar(v_iter_hay_siguiente(iter), "El iterador tiene un siguiente elemento");
    idx = v_iter_siguiente(iter, (void**)&elem);
    pa2m_afirmar(idx == 1, "El índice del segundo elemento es 1");
    pa2m_afirmar(*elem == 2, "El segundo elemento es correcto");

    pa2m_afirmar(v_iter_hay_siguiente(iter), "El iterador tiene un siguiente elemento");
    idx = v_iter_siguiente(iter, (void**)&elem);
    pa2m_afirmar(idx == 2, "El índice del tercer elemento es 2");
    pa2m_afirmar(*elem == 3, "El tercer elemento es correcto");

    pa2m_afirmar(!v_iter_hay_siguiente(iter), "El iterador no tiene más elementos");

    v_iter_destruir(iter);
    vec_destruir(vec);
}

int main() {
    pa2m_nuevo_grupo("============== Pruebas del Vector ===============");

    prueba_crear_vector();
    prueba_insertar_elemento();
    prueba_eliminar_elemento();
    prueba_asignar_elemento();
    prueba_iterar_vector();
    prueba_iterador();

    return pa2m_mostrar_reporte();
}
