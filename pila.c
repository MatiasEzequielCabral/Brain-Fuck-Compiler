#include "pila.h"
#include <stdlib.h>
#define TAMANIO_INICIAL 10
#define FACTOR_DE_CRECIMIENTO 2
#define FACTOR_DE_DECRECIMIENTO 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
//cambia el volumen de una pila
//pre: la pila fue creada.
//post: el tamaño de la pila fue redimensionada.
bool pila_redimensionar(pila_t* pila, size_t capacidad){

	if(capacidad < TAMANIO_INICIAL)
		return false;
	
    pila->datos = realloc(pila->datos, capacidad * sizeof(void*));

    if(pila->datos == NULL){
    	return false;
    }

    pila->capacidad = capacidad;
    return true;
}

// Crea una pila.
// Post: devuelve una nueva pila vacía.
pila_t* pila_crear(void){

	pila_t* pila = malloc(sizeof(pila_t));

    if(pila == NULL)
        return NULL;

    pila->capacidad = TAMANIO_INICIAL;
    pila->datos = malloc(pila->capacidad * sizeof(void*));

    if(pila->capacidad > 0 && pila->datos == NULL){
        free(pila);
        return NULL;
    }

    pila->cantidad = 0;
    return pila;
}

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila){

	free(pila->datos);
	free(pila);
}

// Devuelve verdadero si la pila no tiene elementos apilados, false en caso contrario.
// Pre: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila){

	return pila->cantidad == 0;
}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, void* valor){

	if(pila->cantidad == pila->capacidad)
		pila_redimensionar(pila, (pila->capacidad*FACTOR_DE_CRECIMIENTO));

	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, NULL en caso contrario.
void* pila_ver_tope(const pila_t *pila){

	if(!pila_esta_vacia(pila))
		return pila->datos[pila->cantidad-1];

	return NULL;
}

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// NULL.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.
void* pila_desapilar(pila_t *pila){

	if(pila_esta_vacia(pila))
		return NULL;

	if(pila->cantidad * FACTOR_DE_DECRECIMIENTO <= pila->capacidad)
		pila_redimensionar(pila, (pila->capacidad/FACTOR_DE_DECRECIMIENTO));

	pila->cantidad--;
	return pila->datos[pila->cantidad];
}