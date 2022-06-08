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

void downheap(heap_t* heap, size_t pos_padre);

void swap(void * valores[], size_t pos_A, size_t pos_B){
	void *aux = valores[pos_A];
	valores[pos_A] = valores[pos_B];
	valores[pos_B] = aux;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    if(cant == 0){
        return;
    }
    for (size_t i = 0; i < cant; i++)
    {
        heap_t* heap = heap_crear_arr(elementos, cant-i, cmp);
        swap(heap->valores, MAXIMO, heap->cantidad-1);
        heap_destruir(heap, NULL);
    }
    
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
    heap->cantidad = n;
    heap->funcion_comparar = cmp;

    for (size_t i = 0; i < n; i++){
        heap->valores[i] = arreglo[i];
    }
    for (size_t i = n; i != 0; i--){
        downheap(heap, i - 1);
    }
    return heap;
}

heap_t *heap_crear(cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if (heap == NULL){
        return NULL;
    }
    heap->valores = malloc(sizeof(void*) * TAMANIO_INICIAL);
    if(heap->valores == NULL){
        free(heap);
        return NULL;
    }
    heap->capacidad = TAMANIO_INICIAL;
    heap->cantidad = 0;
    heap->funcion_comparar = cmp;
    return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    for (size_t i = 0; i < heap->cantidad; i++)
    {
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
	return (heap_cantidad(heap) == 0);
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

size_t max(heap_t* heap, size_t pos1, size_t pos2){
	return (heap->funcion_comparar(heap->valores[pos1],heap->valores[pos2]) > 0) ? pos1 : pos2;
}

void downheap(heap_t* heap, size_t pos_padre){
    size_t pos_hijo_izq = (2 * pos_padre) + 1;
    size_t pos_hijo_der = (2 * pos_padre) + 2;
    if(pos_hijo_izq > heap->cantidad-1){
        return;
    }
    size_t pos_maxima;
    if(pos_hijo_der > heap->cantidad-1){
        pos_maxima = pos_hijo_izq;
    }else{
        pos_maxima = max(heap, pos_hijo_izq, pos_hijo_der);

    }

    if(heap->funcion_comparar(heap->valores[pos_padre], heap->valores[pos_maxima]) < 0){
        swap(heap->valores, pos_padre, pos_maxima);
        downheap(heap, pos_maxima);
    }
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
