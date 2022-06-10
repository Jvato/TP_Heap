#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>


int wrapper_strcmp(const void* x, const void* y){
    int i = strcmp((const char*)x, (const char*)y);
    return i;
}

static void prueba_heap_vacio()
{
    printf("INICIO DE PRUEBAS CON HEAP VACIA\n");

    heap_t* heap = heap_crear(wrapper_strcmp);

    print_test("Heap esta vacio", heap_esta_vacio(heap) == true);
    print_test("Heap tiene 0 elementos", heap_cantidad(heap) == 0);
    print_test("Ver el maximo devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar heap devuelve vacio", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
}

static void prueba_heap_encolar_elementos()
{
    printf("INICIO DE PRUEBAS ENCOLAR ELEMENTOS EN HEAP\n");

    heap_t* heap = heap_crear(wrapper_strcmp);  

    char* elem1 = "a";
    char* elem2 = "n";
    char* elem3 = "e";
    char* elem4 = "u";
    char* elem5 = "x";

    print_test("Encolar a es valido", heap_encolar(heap, elem1) == true);
    print_test("Heap tiene 1 elemento", heap_cantidad(heap) == 1);
    print_test("Ver el maximo devuelve a", strcmp(heap_ver_max(heap),"a") == 0);
    print_test("Encolar n es valido", heap_encolar(heap, elem2) == true);
    print_test("Heap tiene 2 elementos", heap_cantidad(heap) == 2);
    print_test("Ver el maximo devuelve n", strcmp(heap_ver_max(heap),"n") == 0);
    print_test("Encolar e es valido", heap_encolar(heap, elem3) == true);
    print_test("Heap tiene 3 elementos", heap_cantidad(heap) == 3);
    print_test("Ver el maximo devuelve n", strcmp(heap_ver_max(heap),"n") == 0);
    print_test("Encolar u es valido", heap_encolar(heap, elem4) == true);
    print_test("Heap tiene 4 elementos", heap_cantidad(heap) == 4);
    print_test("Ver el maximo devuelve u", strcmp(heap_ver_max(heap),"u") == 0);
    print_test("Encolar x es valido", heap_encolar(heap, elem5) == true);
    print_test("Heap tiene 5 elementos", heap_cantidad(heap) == 5);
    print_test("Ver el maximo devuelve x", strcmp(heap_ver_max(heap),"x") == 0);

    heap_destruir(heap, NULL); 
}

static void prueba_heap_desencolar_elementos()
{
    printf("INICIO DE PRUEBAS DESENCOLAR ELEMENTOS EN HEAP\n");

    heap_t* heap = heap_crear(wrapper_strcmp);  

    char* elem1 = "n";
    char* elem2 = "a";
    char* elem3 = "e";
    char* elem4 = "u";

    print_test("Encolar elem1 es valido", heap_encolar(heap, elem1) == true);
    print_test("Encolar elem2 es valido", heap_encolar(heap, elem2) == true);
    print_test("Encolar elem3 es valido", heap_encolar(heap, elem3) == true);
    print_test("Encolar elem4 es valido", heap_encolar(heap, elem4) == true);
    print_test("Ver el maximo devuelve u", strcmp(heap_ver_max(heap),"u") == 0);
    print_test("Desencolar en el heap devuelve u", strcmp(heap_desencolar(heap),"u") == 0);
    print_test("Ver el maximo devuelve n", strcmp(heap_ver_max(heap),"n") == 0);
    print_test("Desencolar en el heap devuelve n", strcmp(heap_desencolar(heap),"n") == 0);
    print_test("Ver el maximo devuelve e", strcmp(heap_ver_max(heap),"e") == 0);
    print_test("Desencolar en el heap devuelve e", strcmp(heap_desencolar(heap),"e") == 0);
    print_test("Ver el maximo devuelve a", strcmp(heap_ver_max(heap),"a") == 0);
    print_test("Desencolar en el heap devuelve a", strcmp(heap_desencolar(heap),"a") == 0);
    print_test("Desencolar en el heap devuelve NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL); 
}

static void prueba_heap_mantiene_invariante()
{
    printf("INICIO DE PRUEBAS HEAP MANTIENE INVARIANTE\n");

    heap_t* heap = heap_crear(wrapper_strcmp);  

    char* elem1 = "n";
    char* elem2 = "a";
    char* elem3 = "e";

    print_test("Encolar n es valido", heap_encolar(heap, elem1) == true);
    print_test("Encolar a es valido", heap_encolar(heap, elem2) == true);
    print_test("Encolar e es valido", heap_encolar(heap, elem3) == true);
    print_test("Desencolar en el heap devuelve n", strcmp(heap_desencolar(heap),"n") == 0);
    print_test("Encolar n es valido", heap_encolar(heap, elem1) == true);
    print_test("Ver el maximo devuelve n nuevamente", strcmp(heap_ver_max(heap),"n") == 0);
    printf("%s\n", (char*)heap_ver_max(heap));
    print_test("Desencolar en el heap devuelve n", strcmp(heap_desencolar(heap),"n") == 0);
    print_test("Desencolar en el heap devuelve e", strcmp(heap_desencolar(heap),"e") == 0);
    print_test("Heap no esta vacio", heap_esta_vacio(heap) == false);
    print_test("Encolar n es valido", heap_encolar(heap, elem1) == true);
    print_test("Encolar e es valido", heap_encolar(heap, elem3) == true);
    print_test("Ver el maximo devuelve n", strcmp(heap_ver_max(heap),"n") == 0);
    print_test("Heap no esta vacio", heap_esta_vacio(heap) == false);

    heap_destruir(heap, NULL); 
}

static void prueba_heap_elementos_dinamicos()
{
    printf("INICIO DE PRUEBAS HEAP CON ELEMENTOS DINAMICOS\n");

    heap_t* heap = heap_crear(wrapper_strcmp);
    
    char* elem1 = malloc(sizeof(char)*2);
    char* elem2 = malloc(sizeof(char)*2);
    char* elem3 = malloc(sizeof(char)*2);
    strcpy(elem1,"n");
    strcpy(elem2,"a");
    strcpy(elem3,"e");

    print_test("Encolar elem1 es valido", heap_encolar(heap, elem1) == true);
    print_test("Encolar elem2 es valido", heap_encolar(heap, elem2) == true);
    print_test("Encolar elem3 es valido", heap_encolar(heap, elem3) == true);
    print_test("Heap tiene 3 elementos", heap_cantidad(heap) == 3);
    print_test("Ver el maximo devuelve n", strcmp(heap_ver_max(heap),"n") == 0);
    print_test("Desencolar en el heap devuelve n", strcmp(heap_desencolar(heap),"n") == 0);
    print_test("Heap tiene 2 elementos", heap_cantidad(heap) == 2);
    free(elem1);
    heap_destruir(heap, free); 
}

int comparar(const void* x, const void* y){
    if(*(int*)x < *(int*)y){
        return -1;
    }else if(*(int*)x == *(int*)y){
        return 0;
    }
    return 1;
}

static void prueba_heap_volumen(size_t tam)
{
    printf("INICIO DE PRUEBAS HEAP VOLUMEN\n");

    heap_t* heap = heap_crear(comparar);


    int numeros[tam];
    for (int i = 0; i < tam; i++){
        numeros[i] = i;
    }

    size_t i;
    bool ok = true;
    for (i = 0; i < tam; i++){
        ok &= heap_encolar(heap, &numeros[i]);
    }
    print_test("Se pudieron encolar todos los elementos", ok);
    print_test("Hay el tamaño deseado de elementos", heap_cantidad(heap) == tam);

    ok = true;
    for (; i > 0; i--) {
        heap_desencolar(heap);
        ok &= heap_cantidad(heap) == (i - 1);
    }
    print_test("Se pudieron desapilar y obtener todos los elementos", ok);
    print_test("Veo que el heap quedo vacio", heap_esta_vacio(heap) == true);
    print_test("Veo que el maximo del heap", heap_ver_max(heap) == NULL);
    print_test("Desencolar de nuevo me da NULL", heap_desencolar(heap) == NULL);

    //Pruebo volver a apilar lo mismo a ver si la pila sigue funcionando como pila    
    for (i = 0; i < tam; i++){
        ok &= heap_encolar(heap, &numeros[i]);
    }
    print_test("Se pudieron encolar todos los elementos por segunda vez", ok);

    heap_destruir(heap, NULL);
}

void mezclar(void* arr[], size_t largo){
    for (size_t i = 0; i < largo; i++){
        size_t indice_aux = (size_t)rand() % largo;
        void* temporal = arr[i];
        arr[i] = arr[indice_aux];
        arr[indice_aux] = temporal;
    }
}

static void prueba_heap_sort()
{
    printf("INICIO DE PRUEBAS HEAPIFY\n");

    size_t largo = 10;
    int numeros[largo];
    for (int i = 0; i < largo; i++)
    {
        numeros[i] = i;
    }
    void* arr[10];
    for (int i = 0; i < largo; i++)
    {
        arr[i] = &numeros[i];
    }
    
    mezclar(arr, largo);
    
    for (size_t i = 0; i < largo; i++){
        printf("%i\n", *(int*)arr[i]);
    }
    heap_sort(arr, largo, comparar);
    printf("Luego de heap sort\n");
    for (size_t i = 0; i < largo; i++){
        printf("%i\n", *(int*)arr[i]);
    }
    
    bool ok = true;
    for (size_t i = 0; i < largo - 1; i++){
        if(arr[i] > arr[i+1]){
            ok = false;
            break;
        }
    }
    print_test("El array esta ordenado", ok);
}

static void prueba_heap_a_partir_de_arreglo()
{
    printf("INICIO DE PRUEBAS CREAR HEAP A PARTIT DE ARREGLO\n");


    size_t largo = 10;
    int numeros[largo];
    for (int i = 0; i < largo; i++)
    {
        numeros[i] = i;
    }
    void* arr[10];
    for (int i = 0; i < largo; i++)
    {
        arr[i] = &numeros[i];
    }
    


    heap_t* heap = heap_crear_arr(arr, 10, comparar);

    int elem1 = 100;

    print_test("Ver el maximo devuelve 9", *(int*)heap_ver_max(heap) == 9);
    print_test("Encolar elem1 es valido", heap_encolar(heap, &elem1) == true);
    print_test("Ver el maximo devuelve 100", *(int*)heap_ver_max(heap) == 100);
    print_test("Heap tiene 2 elementos", heap_cantidad(heap) == 11);
    print_test("Desencolar devuelve 100", *(int*)heap_desencolar(heap) == 100);
    print_test("Desencolar devuelve 9", *(int*)heap_desencolar(heap) == 9);
    print_test("Desencolar devuelve 8", *(int*)heap_desencolar(heap) == 8);

    heap_destruir(heap, NULL); 
}

void pruebas_heap_estudiante()
{
    prueba_heap_vacio();
    prueba_heap_encolar_elementos();
    prueba_heap_desencolar_elementos();
    prueba_heap_mantiene_invariante();
    prueba_heap_elementos_dinamicos();
    prueba_heap_volumen(10000);
    prueba_heap_sort();
    prueba_heap_a_partir_de_arreglo();
}


// void pruebas_volumen_catedra(size_t largo)
// {
//     prueba_heap_volumen(largo);
// }
