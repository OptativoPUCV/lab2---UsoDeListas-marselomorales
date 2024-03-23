#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

List* crea_lista() {
    List* L = create_list();
    if (L == NULL) {
        return NULL; // Manejo de error si create_list() falla
    }

    for (int i = 1; i <= 10; i++) {
        int* elemento = (int*)malloc(sizeof(int)); 
        if (elemento == NULL) {
            // Manejo de error si malloc() falla
            while (get_size(L) > 0) {
                free(popBack(L)); 
            }
            free(L); 
            return NULL;
        }
        *elemento = i; 
        pushBack(L, elemento); 
    }

    return L; 
}



/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) {
    int suma = 0;
    void *dato = first(L); 

    while (dato != NULL) {
        suma += *(int*)dato;
        dato = next(L); 
    }

    return suma; 
}


/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List*L, int elem)
{
  int*current = first(L);
  while(current != NULL)
    {
      if(*current == elem)
        {
          popCurrent(L);
        }
      current = next(L);
    }
}


/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

void copia_pila(List* P1, List* P2) {
    List* auxiliar = create_list(); 

  while (get_size(P1) > 0) {
        void* elemento = popFront(P1);

        pushBack(P2, elemento);
        pushBack(auxiliar, elemento);
    }

    while (get_size(auxiliar) > 0) {
        void* elemento = popBack(auxiliar);

        pushFront(P1, elemento);
    }

    while (get_size(auxiliar) > 0) {
        popFront(auxiliar); 
    }
   
    free(auxiliar);
}



/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

int parentesisBalanceados(char *cadena) {
    List *pila = create_list();

    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] == '(' || cadena[i] == '[' || cadena[i] == '{') {
            pushFront(pila, (void *)&cadena[i]);
        } else if (cadena[i] == ')' || cadena[i] == ']' || cadena[i] == '}') {
            if (get_size(pila) == 0) {
                return 0;
            }
            char *opening = (char *)popFront(pila);
            if ((*opening == '(' && cadena[i] != ')') ||
                (*opening == '[' && cadena[i] != ']') ||
                (*opening == '{' && cadena[i] != '}')) {
                return 0;
            }
        }
    }

    if (get_size(pila) == 0) {
        return 1;
    } else {
        return 0;
    }
}