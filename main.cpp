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
#define NUM_THREADS 4

typedef void *(*funciones)(void *);
void * FIFO(void *);
void * OPT(void *);
void * LRU_cont(void *);
void * LRU_bit(void *);

int buscarEnArreglo(int *, int, int);
int maximo(int *, int);
int calcularDistancia(int *, int *, int);
void avanzarDistancia(int * d, int tamano,int avance);

using namespace std;

int * numeros;
int * fin_numeros;
int size = 0;

int main(int argc, const char * argv[]) {
    funciones funcion[5];
    funcion[0] = FIFO;
    funcion[1] = OPT;
    funcion[2] = LRU_bit;
    funcion[3] = LRU_cont;
    
    
    
    // Leer numeros desde std input
    string a;
    int num;
    while(cin){
        getline(cin, a);
        num = stoi(a);
        numeros[size] = num;
        ++ size;
    }
    fin_numeros = numeros + size;
    
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
    // Arrreglo de paginacion
    int s[STACK];
    int * apuntador = s;
    int * fin_stack = s + STACK;
    memset(s, -1, sizeof(int)*STACK);
    
    int * n = numeros;
    int fallos = 0;
    
    // Simulacion
    int i;
    for (i = 0; i < size; ++i){
        int existencia = buscarEnArreglo(s, *n, STACK);
        if (existencia == -1){
            ++fallos;
            *apuntador = *n;
            ++apuntador;
            if(apuntador >= fin_stack){
                apuntador = s;
            }
        }
        ++n;
    }
    
    // Impresion de numero de fallos
    cout << "FIFO, fallos: " << fallos << endl;
    return 0;
}

void * OPT(void *){
    // Arrreglo de paginacion
    int s[STACK];
    memset(s, -1, sizeof(int)*STACK);
    
    int distancia[STACK];
    memset(distancia, STACK, sizeof(int)*STACK);
    int * n = numeros;
    int fallos = 0;
    
    // Simulacion
    int i;
    int cambio;
    for (i = 0; i < size; ++i){
        int existencia = buscarEnArreglo(s, *n, STACK);
        if (existencia == -1){
            cambio = maximo(distancia, STACK);
            s[cambio] = *n;
            distancia[cambio] = calcularDistancia(n, fin_numeros, *n);
            ++fallos;
        }
        else{
            distancia[existencia] = calcularDistancia(n, fin_numeros, *n);
        }
        avanzarDistancia(distancia, STACK, 1);
        ++n;
    }
    
    cout << "Optimo, fallos: " << fallos << endl;
    return 0;
}

void * LRU_cont(void *){
    // Arrreglo de paginacion
    int s[STACK];
    memset(s, -1, sizeof(int)*STACK);
    
    int tiempo = 0;
    int contador[STACK];
    int * apunt = numeros;
    int fallos = 0;
    // Inicializar los contadores en 0
    memset(contador, 0, sizeof(int)*STACK);
    
    cout << "LRU con contador, fallos: " << fallos << endl;
    return 0;
}

void * LRU_bit(void *){
    // Arrreglo de paginacion
    int s[STACK];
    memset(s, -1, sizeof(int)*STACK);
    
    bool bit[STACK];
    int * apunt;
    int fallos = 0;
    memset(bit, 0, sizeof(bool)*STACK);
    
    cout << "LRU con un bit, fallos: " << fallos << endl;
    return 0;
}

int buscarEnArreglo(int * a, int n, int tamano){
    for (int i = 0; i < tamano; ++i){
        if(n == a[i]){
            return i;
        }
    }
    return -1;
}

int maximo(int * a, int tamano){
    int i;
    int max = 0;
    for (i = 0; i < tamano; ++i){
        if (a[i] > a[0]){
            max = i;
        }
    }
    return max;
}

int calcularDistancia(int * inicio, int * fin, int num){
    int cont = 1;
    int * i = inicio + 1;
    while (i < fin) {
        if (*i == num){
            return cont;
        }
        ++i;
        ++cont;
    }
    return 0;
}

void avanzarDistancia(int * d, int tamano,int avance){
    int i;
    for (i = 0; i < tamano; ++i){
        d[i] = d[i] - avance;
    }
}