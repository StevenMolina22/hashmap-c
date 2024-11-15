#include "pa2m.h"
#include "src/lista.h"

int int_cmp(void* a, void* b) {
    return *(int*)a - *(int*)b;
}

void prueba_creacion_lista() {
    lista_t *lista = lista_crear();
    pa2m_afirmar(lista != NULL, "Se puede crear una lista");
    pa2m_afirmar(lista_cantidad(lista) == 0, "La lista recién creada tiene 0 elementos");
    lista_destruir(lista);
}

void prueba_insercion_lista() {
    lista_t *lista = lista_crear();
    int elemento1 = 10;
    int elemento2 = 20;

    pa2m_afirmar(lista_insertar(lista, 0, &elemento1), "Se puede insertar un elemento en la posición 0");
    pa2m_afirmar(lista_cantidad(lista) == 1, "La lista tiene 1 elemento después de la inserción");
    pa2m_afirmar(lista_insertar(lista, 1, &elemento2), "Se puede insertar un elemento en la posición 1");
    pa2m_afirmar(lista_cantidad(lista) == 2, "La lista tiene 2 elementos después de la inserción");

    lista_destruir(lista);
}

void prueba_agregar_final_lista() {
    lista_t *lista = lista_crear();
    int elemento1 = 10;
    int elemento2 = 20;

    pa2m_afirmar(lista_agregar_final(lista, &elemento1), "Se puede agregar un elemento al final de la lista");
    pa2m_afirmar(lista_cantidad(lista) == 1, "La lista tiene 1 elemento después de agregar al final");
    pa2m_afirmar(lista_agregar_final(lista, &elemento2), "Se puede agregar otro elemento al final de la lista");
    pa2m_afirmar(lista_cantidad(lista) == 2, "La lista tiene 2 elementos después de agregar al final");

    lista_destruir(lista);
}

void prueba_remover_lista() {
    lista_t *lista = lista_crear();
    int elemento1 = 10;
    int elemento2 = 20;

    lista_agregar_final(lista, &elemento1);
    lista_agregar_final(lista, &elemento2);

    int *elemento_removido = lista_remover(lista, 0);
    pa2m_afirmar(elemento_removido == &elemento1, "Se puede remover el primer elemento de la lista");
    pa2m_afirmar(lista_cantidad(lista) == 1, "La lista tiene 1 elemento después de la remoción");

    elemento_removido = lista_remover(lista, 0);
    pa2m_afirmar(elemento_removido == &elemento2, "Se puede remover el segundo elemento de la lista");
    pa2m_afirmar(lista_cantidad(lista) == 0, "La lista tiene 0 elementos después de la remoción");

    lista_destruir(lista);
}

void prueba_buscar_lista() {
    lista_t *lista = lista_crear();
    int elemento1 = 10;
    int elemento2 = 20;

    lista_agregar_final(lista, &elemento1);
    lista_agregar_final(lista, &elemento2);

    int *elemento_encontrado = lista_buscar(lista, &elemento1, &int_cmp);
    pa2m_afirmar(elemento_encontrado == &elemento1, "Se puede buscar y encontrar el primer elemento de la lista");

    elemento_encontrado = lista_buscar(lista, &elemento2, &int_cmp);
    pa2m_afirmar(elemento_encontrado == &elemento2, "Se puede buscar y encontrar el segundo elemento de la lista");

    lista_destruir(lista);
}

void prueba_obtener_lista() {
    lista_t *lista = lista_crear();
    int elemento1 = 10;
    int elemento2 = 20;

    lista_agregar_final(lista, &elemento1);
    lista_agregar_final(lista, &elemento2);

    int *elemento_obtenido = lista_obtener(lista, 0);
    pa2m_afirmar(elemento_obtenido == &elemento1, "Se puede obtener el primer elemento de la lista");

    elemento_obtenido = lista_obtener(lista, 1);
    pa2m_afirmar(elemento_obtenido == &elemento2, "Se puede obtener el segundo elemento de la lista");

    lista_destruir(lista);
}


void prueba_iterador_lista_vacia() {
    lista_t *lista = lista_crear();

    l_iterador_t *iterador = l_iterador_crear(lista);
    pa2m_afirmar(iterador != NULL, "Se puede crear un iterador externo para una lista vacía");
    pa2m_afirmar(!l_iterador_hay_siguiente(iterador), "El iterador no tiene siguiente elemento en una lista vacía");

    l_iterador_destruir(iterador);
    lista_destruir(lista);
}

void prueba_iterador_lista_modificada() {
    lista_t *lista = lista_crear();
    int elemento1 = 10;
    int elemento2 = 20;
    int elemento3 = 30;

    lista_agregar_final(lista, &elemento1);
    lista_agregar_final(lista, &elemento2);

    l_iterador_t *iterador = l_iterador_crear(lista);
    pa2m_afirmar(iterador != NULL, "Se puede crear un iterador externo para la lista");

    lista_agregar_final(lista, &elemento3);
    pa2m_afirmar(l_iterador_hay_siguiente(iterador), "El iterador tiene siguiente elemento después de modificar la lista");
    int *elemento_actual = l_iterador_actual(iterador);
    pa2m_afirmar(elemento_actual == &elemento1, "El iterador apunta al primer elemento de la lista después de modificar la lista");

    l_iterador_avanzar(iterador);
    pa2m_afirmar(l_iterador_hay_siguiente(iterador), "El iterador tiene siguiente elemento después de avanzar");
    elemento_actual = l_iterador_actual(iterador);
    pa2m_afirmar(elemento_actual == &elemento2, "El iterador apunta al segundo elemento de la lista después de avanzar");

    l_iterador_avanzar(iterador);
    pa2m_afirmar(l_iterador_hay_siguiente(iterador), "El iterador tiene siguiente elemento después de avanzar");
    elemento_actual = l_iterador_actual(iterador);
    pa2m_afirmar(elemento_actual == &elemento3, "El iterador apunta al tercer elemento de la lista después de avanzar");

    l_iterador_avanzar(iterador);
    pa2m_afirmar(!l_iterador_hay_siguiente(iterador), "El iterador no tiene más elementos después de avanzar al final");

    l_iterador_destruir(iterador);
    lista_destruir(lista);
}

void prueba_iterador_lista_un_elemento() {
    lista_t *lista = lista_crear();
    int elemento1 = 10;

    lista_agregar_final(lista, &elemento1);

    l_iterador_t *iterador = l_iterador_crear(lista);
    pa2m_afirmar(iterador != NULL, "Se puede crear un iterador externo para una lista con un solo elemento");

    pa2m_afirmar(l_iterador_hay_siguiente(iterador), "El iterador tiene siguiente elemento en una lista con un solo elemento");
    int *elemento_actual = l_iterador_actual(iterador);
    pa2m_afirmar(elemento_actual == &elemento1, "El iterador apunta al único elemento de la lista");

    l_iterador_avanzar(iterador);
    pa2m_afirmar(!l_iterador_hay_siguiente(iterador), "El iterador no tiene más elementos después de avanzar en una lista con un solo elemento");

    l_iterador_destruir(iterador);
    lista_destruir(lista);
}


void prueba_iterador_externo() {
    lista_t *lista = lista_crear();
    int elemento1 = 10;
    int elemento2 = 20;

    lista_agregar_final(lista, &elemento1);
    lista_agregar_final(lista, &elemento2);

    l_iterador_t *iterador = l_iterador_crear(lista);
    pa2m_afirmar(iterador != NULL, "Se puede crear un iterador externo para la lista");

    pa2m_afirmar(l_iterador_hay_siguiente(iterador), "El iterador tiene siguiente elemento");
    int *elemento_actual = l_iterador_actual(iterador);
    pa2m_afirmar(elemento_actual == &elemento1, "El iterador apunta al primer elemento de la lista");

    l_iterador_avanzar(iterador);
    pa2m_afirmar(l_iterador_hay_siguiente(iterador), "El iterador tiene siguiente elemento después de avanzar");
    elemento_actual = l_iterador_actual(iterador);
    pa2m_afirmar(elemento_actual == &elemento2, "El iterador apunta al segundo elemento de la lista después de avanzar");

    l_iterador_avanzar(iterador);
    pa2m_afirmar(!l_iterador_hay_siguiente(iterador), "El iterador no tiene más elementos después de avanzar al final");

    l_iterador_destruir(iterador);
    lista_destruir(lista);
}

int main() {
    pa2m_nuevo_grupo("============== Pruebas del TDA Lista ===============");

    prueba_creacion_lista();
    prueba_insercion_lista();
    prueba_agregar_final_lista();
    prueba_remover_lista();
    prueba_buscar_lista();
    prueba_obtener_lista();
    prueba_iterador_externo();
    prueba_iterador_lista_vacia();
    prueba_iterador_lista_modificada();
    prueba_iterador_lista_un_elemento();

    return pa2m_mostrar_reporte();
}
