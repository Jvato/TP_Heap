#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define TAMANIO_INICIAL 20
#define MAXIMO 0
#define AGRANDAR 2 
#define ACHICAR 2
#define DEBE_ACHICAR 4
#define MINIMO_PARA_ACHICAR 2

struct heap{
    size_t cantidad;
    size_t capacidad;
    void** valores;
    cmp_func_t funcion_comparar;
};

size_t max(heap_t * heap, size_t pos_padre, size_t pos_hijo){
	return (heap->funcion_comparar(heap->valores[pos_padre],heap->valores[pos_hijo]) > 0) ? pos_padre : pos_hijo;
}

void swap(void * valores[], size_t pos_A, size_t pos_B){
	void *aux = valores[pos_A];
	valores[pos_A] = valores[pos_B];
	valores[pos_B] = aux;
}

void downheap(heap_t* heap, size_t pos_padre){
// pregunto si la posicion actual esta dentro de la primera mitad del vector, entonces descarto los "nodos" sin hijos
	if(pos_padre >= heap->cantidad / 2){
       		return;
    	}
    	size_t pos_hijo_izq = (2 * pos_padre) + 1;
    	size_t pos_hijo_der = (2 * pos_padre) + 2;
	size_t pos_maximo;
// pregunta el maximo entre los 2 hijos, encaso que tenga los 2
	if (pos_hijo_izq < heap->cantidad && pos_hijo_der < heap->cantidad) {
		pos_maximo = max(heap,pos_hijo_izq,pos_hijo_der);
	}
// como es un arbol izquierdista, la unica opcion en este punto es que tenga un hijo izq
	else {
		pos_maximo = pos_hijo_izq;
	}
// si lo que hay en pos_maximo es mayor a lo que hay en pos_padre los cambio
    	if (heap->funcion_comparar(heap->valores[pos_maximo],heap->valores[pos_padre]) > 0) {
		swap(heap->valores,pos_maximo,pos_padre);
		downheap(heap,pos_maximo);
	}
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    if(cant == 0){
        return;
    }
    heap_t *heap = heap_crear_arr(elementos, cant, cmp);
    for (size_t i = 0; i < cant; i++) {
	    elementos[i] = heap_desencolar(heap);
    }
    for (size_t i = 0; i < cant/2; i++) {
	    swap(elementos, i, cant-i-1);
    } 
    heap_destruir(heap,NULL);
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if (heap == NULL){
        return NULL;
    }
    heap->valores = malloc(sizeof(void*) * n);
    if(heap->valores == NULL){
        free(heap);
        return NULL;
    }
    heap->capacidad = n;
    heap->cantidad = (arreglo != NULL) ? n : 0;
    heap->funcion_comparar = cmp;
    if ( arreglo != NULL ) { 
	for (size_t i = 0; i < n; i++) {
	    heap->valores[i] = arreglo[i];
	}
// no es necesario pasar por los "nodos" hojas, aplico dowheap solo a los primeros n/2-1 elementos
        for (size_t i = n/2; i != 0; i--){
            downheap(heap,i - 1);
        }
    }
    return heap;
}

heap_t *heap_crear(cmp_func_t cmp){
	return heap_crear_arr(NULL, TAMANIO_INICIAL, cmp);
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    for (size_t i = 0; i < heap->cantidad; i++) {
        if(destruir_elemento != NULL){
            destruir_elemento(heap->valores[i]);
        }
    }
    free(heap->valores);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
	return (heap->cantidad == 0) ? true : false;
}

bool heap_redimensionar(heap_t* heap, size_t nueva_capacidad){
    void** datos_nuevos = realloc(heap->valores, nueva_capacidad * sizeof(void*));
    if(datos_nuevos == NULL){
        return false;
    }
    heap->valores = datos_nuevos;
    heap->capacidad = nueva_capacidad;
    return true;
}

void upheap(heap_t* heap, void* elem, size_t pos){
    if((int)pos-1 < 0){
        return;
    }
    size_t pos_padre = (pos-1)/2;
    if(heap->funcion_comparar(heap->valores[pos_padre], heap->valores[pos]) < 0){
        swap(heap->valores, pos_padre, pos);
        upheap(heap, elem, pos_padre);
    }
}

bool heap_encolar(heap_t *heap, void *elem){
    if(heap->cantidad == heap->capacidad){
        size_t nueva_capacidad = heap->capacidad * AGRANDAR;
        if(!heap_redimensionar(heap, nueva_capacidad)){
            return false;
        }
    }
    if(heap_esta_vacio(heap)){
        heap->valores[MAXIMO] = elem;
    }else{
        heap->valores[heap->cantidad] = elem;
        upheap(heap, elem, heap->cantidad);
    }
    heap->cantidad++;
    return true;
}

void *heap_ver_max(const heap_t *heap){
    return (heap_esta_vacio(heap)? NULL : heap->valores[MAXIMO]);
}

void *heap_desencolar(heap_t *heap){
    if(heap_esta_vacio(heap)){
        return NULL;
    }
    if ((heap->cantidad * DEBE_ACHICAR <= heap->capacidad) && (heap->capacidad / MINIMO_PARA_ACHICAR >= TAMANIO_INICIAL)){
        size_t nueva_capacidad = (heap->capacidad / ACHICAR);
        heap_redimensionar(heap, nueva_capacidad);
    }
    void* valor_a_retornar;
    if(heap->cantidad == 1){
        valor_a_retornar = heap->valores[MAXIMO];
        heap->cantidad--;
    }else{
        swap(heap->valores, MAXIMO, heap->cantidad-1);
        valor_a_retornar = heap->valores[heap->cantidad-1];
        heap->cantidad--;
        downheap(heap, 0);
    }
    return valor_a_retornar;
}
