#include <stdio.h>
#include "src/hash.h"

int main() {
    hash_t* hash = hash_crear(10);
    char clave[] = "Clave";
    char valor[] = "Valor";

    size_t n = 1000;

    // agregar
    for (size_t i = 0; i < n; i++) {
        char clavef[50], valorf[50];
        snprintf(clavef, sizeof(clavef), "%s %zu", clave, i);
        snprintf(valorf, sizeof(valorf), "%s %zu", valor, i);
        hash_insertar(hash, clavef, valorf, NULL);
    }

    // buscar
    for (size_t i = 0; i < n; i++) {
        char clavef[50];
        snprintf(clavef, sizeof(clavef), "%s %zu", clave, i);
        char* valor = hash_buscar(hash, clavef);
        if (!valor) {
            printf("No encontrado\n");
        } else {
            printf("%s\n", valor);
        }

    }
    return 0;
}
