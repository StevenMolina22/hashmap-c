// nodo_t* nodo_crear(char* clave, void* valor) {
//     nodo_t* entrada = calloc(1, sizeof(nodo_t));
//     if (!entrada)
//         return NULL;
//     entrada->clave = clave;
//     entrada->valor = valor;
//     return entrada;
// }
void hihi(){

}
// void nodo_destruir(nodo_t *nodo, fndest_t destructor) {
//     if (!nodo)
//         return;
//     free(nodo->clave);
//     if (destructor)
//         destructor(nodo->valor);
//     free(nodo);
// }

// void nodos_destruir(nodo_t *nodo, fndest_t destructor) {
//     while (nodo) {
//         nodo_destruir(nodo, destructor);
//         nodo = nodo->sig;
//     }
// }

// bool nodos_insertar(nodo_t *primero, char* clave, void* valor) {
//     nodo_t* nuevo = nodo_crear(clave, valor);
//     if (!nuevo)
//         return false;
//     nodo_t* temp = primero;
//     primero->ant = nuevo;
//     nuevo->sig = temp;
//     return true;
// }

// void* nodo_remover(nodo_t *primero, char* clave) {
//     nodo_t* encontrado = nodo_buscar(primero, clave);
//     if (!encontrado)
//         return NULL;
//     if (encontrado->ant && encontrado->sig) {
//         nodo_t* siguiente = encontrado->sig;
//         siguiente->ant = NULL;
//         encontrado = ?????;
//     }
//     nodo_t* temp = encontrado;
// }

// nodo_t* nodo_buscar(nodo_t *nodo, char* clave) {
//     while (nodo) {
//         if (strcmp(nodo->clave, clave) == 0) {
//             return nodo;
//             nodo = nodo->sig;
//         }
//     }
//     return NULL;
// }
