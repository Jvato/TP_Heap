#include "heap.h"

#define TAMANIO_INICIAL 50
#define MAXIMO 0
#define AGRANDAR 2 
#define ACHICAR 2
#define DEBE_ACHICAR 4
#define MINIMO_PARA_ACHICAR 2

void swap(void* elem1, void* elem2){

}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    if(cant == 0){
        return;
    }
    heap_t* heap = heap_crear_arr(elementos, cant, cmp);
    swap(heap->valores[MAXIMO], heap->valores[heap->cantida]);
    heap_crear_arr(heap->valores, heap->cantida-1, cmp);
}

struct heap{
    size_t cantida;
    size_t capacidad;
    void** valores;
    cmp_func_t funcion_comparar;
};

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
    heap->cantida = 0;
    heap->funcion_comparar = cmp;
    return heap;
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
    for (size_t i = 0; i < n; i++){
        heap->valores = arreglo[i];
    }
    heap->capacidad = n;
    heap->cantida = n;
    heap->funcion_comparar = cmp;
    
    for (size_t i = n; i != 0; i--){
        downheap(heap, i);
    }
    
    return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    for (size_t i = 0; i < heap->cantida; i++){
        if(destruir_elemento != NULL){
            destruir_elemento(heap->valores[i]);
        }
    }
    free(heap->valores);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cantida;
}

bool heap_esta_vacio(const heap_t *heap){
    if(heap_cantidad(heap) == 0){
        return true;
    }
    return false;
}


bool heap_redimensionar(heap_t* heap, size_t nueva_capacidad){
    void** datos_nuevos = realloc(heap->valores, nueva_capacidad);
    if(datos_nuevos == NULL){
        return false;
    }
    heap->valores = datos_nuevos;
    heap->capacidad = nueva_capacidad;
    return true;
}

void upheap(heap_t* heap, void* elem, size_t pos){
    if(pos-1 < 0){
        return;
    }
    size_t pos_padre = (pos-1)/2;
    if(heap->funcion_comparar(heap->valores[pos_padre], heap->valores[pos]) < 0){
        swap(heap->valores[pos_padre], heap->valores[pos]);
        upheap(heap, elem, pos_padre);
    }
}

bool heap_encolar(heap_t *heap, void *elem){
    if(heap->cantida == heap->capacidad){
        size_t nueva_capacidad = heap->capacidad * AGRANDAR;
        if(!heap_redimensionar(heap, nueva_capacidad)){
            return false;
        }
    }
    heap->valores[heap->cantida+1] = elem;
    upheap(heap, elem, heap->cantida+1);
    heap->cantida++;
    return true;
}

void *heap_ver_max(const heap_t *heap){
    return (heap_esta_vacio(heap)? NULL : heap->valores[MAXIMO]);
}

void* max(cmp_func_t cmp, void* padre, void* hijo_izq, void* hijo_der){
    
}


void downheap(heap_t* heap, size_t padre){
    if(padre+1 > heap->cantida){
        return;
    }
    size_t pos_hijo_izq = (2*padre) + 1;
    size_t pos_hijo_der = (2*padre) + 2;
    void* maximo = max(heap->funcion_comparar, heap->valores[padre], heap->valores[pos_hijo_izq], heap->valores[pos_hijo_der]);
    if(maximo != heap->valores[padre]){
        swap(maximo, heap->valores[padre]);
        downheap(heap, maximo);
    }

}

void *heap_desencolar(heap_t *heap){
    if(heap_esta_vacio(heap)){
        return NULL;
    }
    if ((heap->cantida * DEBE_ACHICAR <= heap->capacidad) && (heap->capacidad / MINIMO_PARA_ACHICAR >= TAMANIO_INICIAL)){
        size_t nueva_capacidad = (heap->capacidad / ACHICAR);
        heap_redimensionar(heap, nueva_capacidad);
    }
    swap(heap->valores[MAXIMO], heap->valores[heap->cantida]);
    void* valor_a_retornar = heap->valores[heap->cantida];
    heap->cantida--;
    downheap(heap, 0);
    return valor_a_retornar;
}
