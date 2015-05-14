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
#include <fstream>
#include <vector>
#include <string>
#include "pthread.h"

#define STACK 100
#define NUM_THREADS 4

typedef void *(*funciones)(void *);
void * FIFO(void *);
void * OPT(void *);
void * LRU_cont(void *);
void * LRU_bit(void *);

int buscarEnArreglo(int *, int, int);
int maximo(int *, int);
int minimo(int *, int);
int calcularDistancia(int *, int *, int);
void avanzarDistancia(int * d, int tamano,int avance);

using namespace std;


int * numeros;
int * fin_numeros;
int tamo = 0;


int main(int argc, const char * argv[]) {
    funciones funcion[5];
    funcion[0] = FIFO;
    funcion[1] = OPT;
    funcion[2] = LRU_bit;
    funcion[3] = LRU_cont;
    
    vector<int> provisional;
    
    // Leer numeros desde std input
    string a;
    int num;
    while(1){
        if (feof(stdin)){
            break;
        }
        
        fscanf(stdin, "%d", &num);
        provisional.push_back(num);
    }
    
    numeros = new int[provisional.size()];
    int* indice = numeros;
    for(auto item:provisional){
        *indice = item;
        // cout << item << endl;
        ++indice;
    }
    tamo = provisional.size();
    
    fin_numeros = numeros + tamo -1;
    
    FIFO(0);
    OPT(0);
    LRU_bit(0);
    LRU_cont(0);
    
    // Crear threads para los distintos algoritmos
    
    /*
    pthread_t threads[NUM_THREADS];
    int rc;
    for (int i = 0; i < NUM_THREADS; i++){
        rc = pthread_create(&threads[i], NULL, funcion[i], 0);
        if (rc){
            cout<< "No se pudo crear el thread " << i << "\n";
        }
    }
    */
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
    for (i = 0; i < tamo; ++i){
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
    for (i = 0; i < tamo; ++i){
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
    
    int tiempo = 1;
    int contador[STACK];
    int * apunt = numeros;
    int fallos = 0;
    // Inicializar los contadores en 0
    memset(contador, -10, sizeof(int)*STACK);
    
    // Simulador
    int i;
    for (i = 0; i < tamo; ++i){
        int existencia = buscarEnArreglo(s, *apunt, STACK);
        if (existencia != -1){
            contador[existencia] = tiempo;
        }
        else{
            int viejo = minimo(contador, STACK);
            s[viejo] = *apunt;
            contador[viejo] = tiempo;
            fallos++;
        }
        
        ++tiempo;
        ++apunt;
    }
    
    cout << "LRU con contador, fallos: " << fallos << endl;
    return 0;
}

void * LRU_bit(void *){
    // Arrreglo de paginacion
    int s[STACK];
    memset(s, -1, sizeof(int)*STACK);
    
    int bit[STACK];
    int * apunt = numeros;
    int fallos = 0;
    memset(bit, 0, sizeof(bool)*STACK);
    int pos = 0;
    
    // Simulacion
    for(int i = 0; i < tamo; ++i){
        int existencia = buscarEnArreglo(s, *apunt, STACK);
        if (existencia != -1){
            //cout << "encontrado" << endl;
            bit[existencia] = 1;
        }
        else{
            fallos++;
            while (bit[pos] != 0){
                bit[pos] = 0;
                ++pos;
                if (pos >= STACK){
                    pos = 0;
                }
            }
            bit[pos] = 1;
            s[pos] = *apunt;
            
        }
        
        ++apunt;
    }
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

int minimo(int * a, int tamano){
    int i;
    int min = -10;
    for (i = 0; i < tamano; ++i){
        if (a[i] < a[min]){
            min = i;
        }
    }
    return min;
}

int maximo(int * a, int tamano){
    int i;
    int max = 0;
    for (i = 0; i < tamano; ++i){
        if (a[i] > a[max]){
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