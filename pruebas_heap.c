#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void prueba_heap_vacio()
{
    printf("INICIO DE PRUEBAS CON HEAP VACIA\n");

    heap_t* heap = heap_crear(strcmp);

    print_test("Heap esta vacio", heap_esta_vacio(heap) == true);
    print_test("Heap tiene 0 elementos", heap_cantidad(heap) == 0);
    print_test("Ver el maximo devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar heap devuelve vacio", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
}

static void prueba_heap_encolar_elementos()
{
    printf("INICIO DE PRUEBAS ENCOLAR ELEMENTOS EN HEAP\n");

    heap_t* heap = heap_crear(strcmp);  

    char* elem1 = "a";
    char* elem2 = "n";
    char* elem3 = "e";
    char* elem4 = "u";
    char* elem5 = "x";

    print_test("Encolar elem1 es valido", heap_encolar(heap, elem1) == true);
    print_test("Heap tiene 1 elemento", heap_cantidad(heap) == 1);
    print_test("Ver el maximo devuelve a", heap_ver_max(heap) == "a");
    print_test("Encolar elem2 es valido", heap_encolar(heap, elem2) == true);
    print_test("Heap tiene 2 elementos", heap_cantidad(heap) == 2);
    print_test("Ver el maximo devuelve n", heap_ver_max(heap) == "n");
    print_test("Encolar elem3 es valido", heap_encolar(heap, elem3) == true);
    print_test("Heap tiene 3 elementos", heap_cantidad(heap) == 3);
    print_test("Ver el maximo devuelve n", heap_ver_max(heap) == "n");
    print_test("Encolar elem4 es valido", heap_encolar(heap, elem4) == true);
    print_test("Heap tiene 4 elementos", heap_cantidad(heap) == 4);
    print_test("Ver el maximo devuelve u", heap_ver_max(heap) == "u");
    print_test("Encolar elem5 es valido", heap_encolar(heap, elem5) == true);
    print_test("Heap tiene 5 elementos", heap_cantidad(heap) == 5);
    print_test("Ver el maximo devuelve x", heap_ver_max(heap) == "x");

    heap_destruir(heap, NULL); 
}

static void prueba_heap_desencolar_elementos()
{
    printf("INICIO DE PRUEBAS ENCOLAR ELEMENTOS EN HEAP\n");

    heap_t* heap = heap_crear(strcmp);  

    char* elem1 = "n";
    char* elem2 = "a";
    char* elem3 = "e";
    char* elem4 = "u";

    print_test("Encolar elem1 es valido", heap_encolar(heap, elem1) == true);
    print_test("Encolar elem2 es valido", heap_encolar(heap, elem2) == true);
    print_test("Encolar elem3 es valido", heap_encolar(heap, elem3) == true);
    print_test("Encolar elem4 es valido", heap_encolar(heap, elem4) == true);
    print_test("Ver el maximo devuelve u", heap_ver_max(heap) == "u");
    print_test("Desencolar en el heap devuelve u", heap_desencolar(heap) == "u");
    print_test("Ver el maximo devuelve n", heap_ver_max(heap) == "n");
    print_test("Desencolar en el heap devuelve n", heap_desencolar(heap) == "n");
    print_test("Ver el maximo devuelve e", heap_ver_max(heap) == "e");
    print_test("Desencolar en el heap devuelve e", heap_desencolar(heap) == "e");
    print_test("Ver el maximo devuelve a", heap_ver_max(heap) == "a");
    print_test("Desencolar en el heap devuelve a", heap_desencolar(heap) == "a");
    print_test("Desencolar en el heap devuelve NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL); 
}

static void prueba_heap_mantiene_invariante()
{
    printf("INICIO DE PRUEBAS HEAP MANTIENE INVARIANTE\n");

    heap_t* heap = heap_crear(strcmp);  

    char* elem1 = "n";
    char* elem2 = "a";
    char* elem3 = "e";

    print_test("Encolar elem1 es valido", heap_encolar(heap, elem1) == true);
    print_test("Encolar elem2 es valido", heap_encolar(heap, elem2) == true);
    print_test("Encolar elem3 es valido", heap_encolar(heap, elem3) == true);
    print_test("Desencolar en el heap devuelve n", heap_desencolar(heap) == "n");
    print_test("Encolar elem1 es valido", heap_encolar(heap, elem1) == true);
    print_test("Ver el maximo devuelve n nuevamente", heap_ver_max(heap) == "n");
    print_test("Desencolar en el heap devuelve e", heap_desencolar(heap) == "e");
    print_test("Desencolar en el heap devuelve a", heap_desencolar(heap) == "a");
    print_test("Heap esta vacio", heap_esta_vacio(heap) == true);
    print_test("Encolar elem1 es valido", heap_encolar(heap, elem1) == true);
    print_test("Encolar elem2 es valido", heap_encolar(heap, elem2) == true);
    print_test("Ver el maximo devuelve n", heap_ver_max(heap) == "n");
    print_test("Heap no esta vacio", heap_esta_vacio(heap) == false);

    heap_destruir(heap, NULL); 
}

static void prueba_heap_elementos_dinamicos()
{
    printf("INICIO DE PRUEBAS HEAP MANTIENE INVARIANTE\n");

    heap_t* heap = heap_crear(strcmp);
    
    char* elem1 = malloc(sizeof(char*));
    char* elem2 = malloc(sizeof(char*));
    char* elem3 = malloc(sizeof(char*));
    elem1 = "n";
    elem2 = "a";
    elem3 = "e";

    print_test("Encolar elem1 es valido", heap_encolar(heap, elem1) == true);
    print_test("Encolar elem2 es valido", heap_encolar(heap, elem2) == true);
    print_test("Encolar elem3 es valido", heap_encolar(heap, elem3) == true);
    print_test("Heap tiene 3 elementos", heap_cantidad(heap) == 3);
    print_test("Ver el maximo devuelve n", heap_ver_max(heap) == "n");
    print_test("Desencolar en el heap devuelve n", heap_desencolar(heap) == "n");
    print_test("Heap tiene 2 elementos", heap_cantidad(heap) == 2);

    heap_destruir(heap, free); 
}

int comparar(int x, int y){
    if(x < y){
        return -1;
    }else if(x == y){
        return 0;
    }
    return 1;
}

static void prueba_heap_volumen()
{
    printf("INICIO DE PRUEBAS HEAP VOLUMEN\n");

    heap_t* heap = heap_crear(comparar);
    size_t tam = 1000;

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

    ok = true;
    int valor;
    for (; i > 0; i--) {
        valor = *(int*)heap_desencolar(heap);
        if(heap_esta_vacio(heap)){
            ok = false;
        }
        ok &= heap_cantidad(heap) == (i - 1);
    }
    print_test("Se pudieron desapilar y obtener todos los elementos", ok);
    print_test("Veo que la pila quedo vacia", heap_esta_vacio(heap) == true);
    print_test("Veo que el maximo del heap", heap_ver_max(heap) == NULL);
    print_test("Desencolar de nuevo me da NULL", heap_desencolar(heap) == NULL);

    //Pruebo volver a apilar lo mismo a ver si la pila sigue funcionando como pila    
    for (i = 0; i < tam; i++){
        ok &= heap_encolar(heap, &numeros[i]);
    }
    print_test("Se pudieron encolar todos los elementos por segunda vez", ok);

    heap_destruir(heap, NULL);
}

void mezclar(int arr[], size_t largo){
    for (size_t i = 0; i < largo; i++){
        int indice_aux = rand() % largo;
        int temporal = arr[i];
        arr[i] = arr[indice_aux];
        arr[indice_aux] = temporal;
    }
}


static void prueba_heap_heapify()
{
    printf("INICIO DE PRUEBAS HEAPIFY\n");

    int largo = 10;
    int arr[largo];
    for (size_t i = 0; i < largo; i++){
        arr[i] = i;
    }
    
    mezclar(arr, largo);
    
    bool ok = true;
    for (size_t i = 0; i < largo-1; i++){
        if(arr[i] > arr[i+1]){
            ok = false;
            break;
        }
    }
    print_test("El array esta arreglado", ok);
}

static void prueba_heap_a_partir_de_arreglo()
{
    printf("INICIO DE PRUEBAS CREAR HEAP A PARTIT DE ARREGLO\n");

    int largo = 10;
    int arr[largo];
    for (size_t i = 0; i < largo; i++){
        arr[i] = i;
    }
    
    mezclar(arr, largo);

    heap_t* heap = heap_crear_arr(arr, largo, comparar);

    int elem1 = 1;
    int elem2 = 3;
    int elem3 = 2;


    print_test("Encolar elem1 es valido", heap_encolar(heap, &elem1) == true);
    print_test("Heap tiene 1 elemento", heap_cantidad(heap) == 1);
    print_test("Ver el maximo devuelve 1", *(int*)heap_ver_max(heap) == 1);
    print_test("Encolar elem2 es valido", heap_encolar(heap, &elem2) == true);
    print_test("Heap tiene 2 elementos", heap_cantidad(heap) == 2);
    print_test("Ver el maximo devuelve 3", *(int*)heap_ver_max(heap) == 3);
    print_test("Encolar elem3 es valido", heap_encolar(heap, &elem3) == true);
    print_test("Heap tiene 3 elementos", heap_cantidad(heap) == 3);
    print_test("Ver el maximo devuelve 3", *(int*)heap_ver_max(heap) == 3);
    print_test("Desencolar devuelve 3", *(int*)heap_desencolar(heap) == 3);

    heap_destruir(heap, NULL); 
}

void pruebas_heap_estudiante()
{
    prueba_heap_vacio();
    prueba_heap_encolar_elementos();
    prueba_heap_desencolar_elementos();
    prueba_heap_mantiene_invariante();
    prueba_heap_elementos_dinamicos();
    prueba_heap_volumen();
    prueba_heap_heapify();
    prueba_heap_a_partir_de_arreglo();
}
