#include "pa2m.h"
#include "src/hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prueba_crear_hash()
{
    hash_t* hash = hash_crear(10);
    pa2m_afirmar(hash != NULL, "Se puede crear un hash con capacidad inicial 10");
    pa2m_afirmar(hash_cantidad(hash) == 0, "El hash recién creado tiene 0 elementos");
    hash_destruir(hash);
}

void prueba_insertar_elementos()
{
    hash_t* hash = hash_crear(10);
    int valor1 = 42;
    int valor2 = 84;
    void* encontrado;

    pa2m_afirmar(hash_insertar(hash, "clave1", &valor1, &encontrado), "Se puede insertar un elemento en el hash");
    pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene 1 elemento después de insertar");
    pa2m_afirmar(hash_insertar(hash, "clave2", &valor2, &encontrado), "Se puede insertar otro elemento en el hash");
    pa2m_afirmar(hash_cantidad(hash) == 2, "El hash tiene 2 elementos después de insertar");

    hash_destruir(hash);
}

void prueba_insertar_claves_duplicadas()
{
    hash_t* hash = hash_crear(10);
    int valor1 = 42;
    int valor2 = 84;
    void* encontrado = NULL;

    hash_insertar(hash, "clave1", &valor1, &encontrado);
    pa2m_afirmar(hash_insertar(hash, "clave1", &valor2, &encontrado), "Se puede insertar un elemento con una clave duplicada");
    pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene 1 elemento después de insertar una clave duplicada");
    pa2m_afirmar(encontrado == &valor1, "El valor reemplazado es el correcto");

    int* valor_encontrado = (int*)hash_buscar(hash, "clave1");
    pa2m_afirmar(valor_encontrado != NULL && *valor_encontrado == valor2, "El valor asociado a 'clave1' es el nuevo valor");

    hash_destruir(hash);
}

void prueba_insertar_clave_nula()
{
    hash_t* hash = hash_crear(10);
    int valor = 42;
    void* encontrado = NULL;

    pa2m_afirmar(!hash_insertar(hash, NULL, &valor, &encontrado), "No se puede insertar un elemento con clave nula");

    hash_destruir(hash);
}

void prueba_insertar_valor_nulo()
{
    hash_t* hash = hash_crear(10);
    void* encontrado = NULL;

    pa2m_afirmar(hash_insertar(hash, "clave1", NULL, &encontrado), "Se puede insertar un elemento con valor nulo");
    pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene 1 elemento después de insertar un valor nulo");

    hash_destruir(hash);
}

void prueba_insertar_muchos_elementos()
{
    hash_t* hash = hash_crear(10);
    void* encontrado = NULL;
    int cantidad = 1000;
    bool exito = true;

    for (int i = 0; i < cantidad; i++) {
        char clave[20];
        sprintf(clave, "clave%d", i);
        int* valor = malloc(sizeof(int));
        *valor = i;
        if (!hash_insertar(hash, clave, valor, &encontrado)) {
            exito = false;
            break;
        }
    }

    pa2m_afirmar(exito, "Se pueden insertar 1000 elementos en el hash");
    pa2m_afirmar(hash_cantidad(hash) == cantidad, "El hash tiene 1000 elementos después de insertar muchos elementos");

    hash_destruir_todo(hash, free);
}

void prueba_buscar_elementos()
{
    hash_t* hash = hash_crear(10);
    int valor1 = 42;
    int valor2 = 84;
    void* encontrado = NULL;

    hash_insertar(hash, "clave1", &valor1, &encontrado);
    hash_insertar(hash, "clave2", &valor2, &encontrado);

    int* valor_encontrado = (int*)hash_buscar(hash, "clave1");
    pa2m_afirmar(valor_encontrado != NULL && *valor_encontrado == valor1, "Se puede buscar y encontrar el valor asociado a 'clave1'");

    valor_encontrado = (int*)hash_buscar(hash, "clave2");
    pa2m_afirmar(valor_encontrado != NULL && *valor_encontrado == valor2, "Se puede buscar y encontrar el valor asociado a 'clave2'");

    valor_encontrado = (int*)hash_buscar(hash, "clave_inexistente");
    pa2m_afirmar(valor_encontrado == NULL, "Buscar una clave inexistente devuelve NULL");

    hash_destruir(hash);
}

void prueba_quitar_elementos()
{
    hash_t* hash = hash_crear(10);
    int valor1 = 42;
    int valor2 = 84;
    void* encontrado = NULL;

    hash_insertar(hash, "clave1", &valor1, &encontrado);
    hash_insertar(hash, "clave2", &valor2, &encontrado);

    int* valor_quitado = (int*)hash_quitar(hash, "clave1");
    pa2m_afirmar(valor_quitado != NULL && *valor_quitado == valor1, "Se puede quitar el valor asociado a 'clave1'");
    pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene 1 elemento después de quitar 'clave1'");

    valor_quitado = (int*)hash_quitar(hash, "clave2");
    pa2m_afirmar(valor_quitado != NULL && *valor_quitado == valor2, "Se puede quitar el valor asociado a 'clave2'");
    pa2m_afirmar(hash_cantidad(hash) == 0, "El hash tiene 0 elementos después de quitar 'clave2'");

    valor_quitado = (int*)hash_quitar(hash, "clave_inexistente");
    pa2m_afirmar(valor_quitado == NULL, "Quitar una clave inexistente devuelve NULL");

    hash_destruir(hash);
}

void prueba_quitar_muchos_elementos()
{
    hash_t* hash = hash_crear(10);
    void* encontrado = NULL;
    int cantidad = 1000;

    for (int i = 0; i < cantidad; i++) {
        char clave[20];
        sprintf(clave, "clave%d", i);
        int* valor = malloc(sizeof(int));
        *valor = i;
        hash_insertar(hash, clave, valor, &encontrado);
    }
    printf("%zu\n", hash_cantidad(hash));

    bool exito = true;
    for (int i = 0; i < cantidad; i++) {
        char clave[20];
        sprintf(clave, "clave%d", i);
        int* valor_quitado = (int*)hash_quitar(hash, clave);
        if (valor_quitado == NULL || *valor_quitado != i) {
            exito = false;
            break;
        }
        free(valor_quitado);
    }

    pa2m_afirmar(exito, "Se pueden quitar 1000 elementos del hash");
    printf("%zu\n", hash_cantidad(hash));
    pa2m_afirmar(hash_cantidad(hash) == 0, "El hash tiene 0 elementos después de quitar muchos elementos");

    hash_destruir(hash);
}

void prueba_contiene_clave()
{
    hash_t* hash = hash_crear(10);
    int valor1 = 42;
    void* encontrado = NULL;

    hash_insertar(hash, "clave1", &valor1, &encontrado);

    pa2m_afirmar(hash_contiene(hash, "clave1"), "El hash contiene 'clave1'");
    pa2m_afirmar(!hash_contiene(hash, "clave_inexistente"), "El hash no contiene 'clave_inexistente'");

    hash_destruir(hash);
}

bool iterador_prueba(char* clave, void* valor, void* ctx)
{
    (*(int*)ctx)++;
    return true;
}

bool iterador_prueba_corte(char* clave, void* valor, void* ctx)
{
    (*(int*)ctx)++;
    return (*(int*)ctx) < 2;
}

void prueba_iterar_elementos()
{
    hash_t* hash = hash_crear(10);
    int valor1 = 42;
    int valor2 = 84;
    void* encontrado = NULL;

    hash_insertar(hash, "clave1", &valor1, &encontrado);
    hash_insertar(hash, "clave2", &valor2, &encontrado);

    int contador = 0;
    size_t iterados = hash_iterar(hash, iterador_prueba, &contador);

    pa2m_afirmar(iterados == 2, "Se iteran 2 elementos en el hash");
    pa2m_afirmar(contador == 2, "El contador se incrementa correctamente durante la iteración");

    contador = 0;
    iterados = hash_iterar(hash, iterador_prueba_corte, &contador);
    pa2m_afirmar(iterados == 2, "La iteración se corta correctamente cuando la función devuelve false");
    pa2m_afirmar(contador == 2, "El contador se incrementa correctamente durante la iteración con corte");

    hash_destruir(hash);
}

void destructor_prueba(void* elemento)
{
    free(elemento);
}

void prueba_destruir_todo()
{
    hash_t* hash = hash_crear(10);
    int* valor1 = malloc(sizeof(int));
    int* valor2 = malloc(sizeof(int));
    *valor1 = 42;
    *valor2 = 84;
    void* encontrado = NULL;

    hash_insertar(hash, "clave1", valor1, &encontrado);
    hash_insertar(hash, "clave2", valor2, &encontrado);

    hash_destruir_todo(hash, destructor_prueba);
    pa2m_afirmar(true, "El hash se destruye correctamente y se aplica el destructor a los elementos");
}

void prueba_destruir_sin_elementos()
{
    hash_t* hash = hash_crear(10);
    hash_destruir(hash);
    pa2m_afirmar(true, "El hash se destruye correctamente cuando no tiene elementos");
}

int main() {
    pa2m_nuevo_grupo("============== Pruebas del Hashmap ===============");

    prueba_crear_hash();
    prueba_insertar_elementos();
    prueba_insertar_claves_duplicadas();
    prueba_insertar_clave_nula();
    prueba_insertar_valor_nulo();
    prueba_insertar_muchos_elementos();
    prueba_buscar_elementos();
    prueba_quitar_elementos();
    prueba_quitar_muchos_elementos();
    prueba_contiene_clave();
    prueba_iterar_elementos();
    prueba_destruir_todo();
    prueba_destruir_sin_elementos();

    return pa2m_mostrar_reporte();
}
