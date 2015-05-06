//
//  main.cpp
//  proyecto_so
//
//  Created by:
//  Daniel Monzalvo A01021514
//  Marcos Lopez A01020023
//  on 05/05/15.
//

#include <iostream>
#include <string>
#include "pthread.h"

#define STACK 1000
#define NUM_THREADS 5

typedef void *(*funciones)(void *);
void * FIFO(void *);
void * OPT(void *);
void * LRU_cont(void *);
void * LRU_bit(void *);
void * LRU_dbits(void *);

using namespace std;

int * numeros;
int size = 0;

int main(int argc, const char * argv[]) {
    funciones funcion[5];
    funcion[0] = FIFO;
    funcion[1] = OPT;
    funcion[2] = LRU_bit;
    funcion[3] = LRU_cont;
    funcion[4] = LRU_dbits;
    
    
    
    // Leer numeros desde std input
    string a;
    int num;
    while(cin){
        getline(cin, a);
        num = stoi(a);
        numeros[size] = num;
        ++ size;
    }
    
    // Crear threads para los distintos algoritmos
    
    pthread_t threads[NUM_THREADS];
    int rc;
    for (int i = 0; i < NUM_THREADS; i++){
        rc = pthread_create(&threads[i], NULL, funcion[i], 0);
        if (rc){
            cout<< "No se pudo crear el thread " << i << "\n";
        }
    }
    return 0;
}


void * FIFO(void *){
    int * apunt = numeros;
    
    return 0;
}

void * OPT(void *){
    int distancia[STACK];
    int * apunt = numeros;
    
    return 0;
}

void * LRU_cont(void *){
    int contador[STACK];
    int * apunt = numeros;
    
    return 0;
}

void * LRU_bit(void *){
    bool bit[STACK];
    int * apunt;
    
    return 0;
}

void * LRU_dbits(void *){
    bool bitl[STACK];
    bool bire[STACK];
    
    return 0;
}