// TITLE: Algoritmos Práctica 4
// AUTHOR 1: Miguel López López        LOGIN 1: m.llopez
// AUTHOR 2: Ángel Gómez prol          LOGIN 2: angel.gomez.prol
// AUTHOR 3: Xoel Díaz Préstamo        LOGIN 3: xoel.diaz
// GROUP: 2.1.4
// DATE: 22/11/2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#define TAM_MAX 1600
typedef int ** matriz;
typedef struct {
    int x, y, peso;
} arista;

typedef arista tipo_elemento;
typedef struct {
    int cabeza, final, tamano;
    tipo_elemento vector[TAM_MAX];
} cola;

void crear_cola(cola *);
int cola_vacia(cola);
void insertar(tipo_elemento, cola *);
tipo_elemento quitar_primero(cola *);
tipo_elemento primero(cola);
void mostrar_cola(cola);

void crear_cola(cola *c) {
    c->tamano = 0;
    c->cabeza = 0;
    c->final = -1;
}
int cola_vacia(cola c) {
    return (c.tamano == 0);
}
void incrementar(int *x) {/* privado */
    if (++(*x) == TAM_MAX)
        *x = 0;
}
void insertar(tipo_elemento x, cola *c) {
    if (c->tamano == TAM_MAX) {
        printf("error: cola llena: %d\n", c->tamano);
        exit(EXIT_FAILURE);
    }
    c->tamano++;
    incrementar(&(c->final));
    c->vector[c->final] = x;
}
tipo_elemento primero(cola c) {
    if (cola_vacia(c)) {
        printf("error: cola vacia\n"); exit(EXIT_FAILURE);
    }
    return(c.vector[c.cabeza]);
}
tipo_elemento quitar_primero(cola *c) {
    tipo_elemento x;
    if (cola_vacia(*c)) {
        printf("error: cola vacia\n");
        exit(EXIT_FAILURE);
    }
    c->tamano--;
    x = c->vector[c->cabeza];
    incrementar(&(c->cabeza));
    return x;
}

double microsegundos() {  /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

matriz crear_matriz(int n) {
    int i;
    matriz aux;
    if ((aux = malloc(n*sizeof(int *))) == NULL)
        return NULL;
    for (i=0; i<n; i++)
        if ((aux[i] = malloc(n*sizeof(int))) == NULL)
            return NULL;
    return aux;
}

void inicializar_matriz(matriz m, int n) {
/* Crea un grafo completo no dirigido con valores aleatorios entre 1 y n */
    int i, j;
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            m[i][j] = rand() % n + 1;

    for (i=0; i<n; i++)
        for (j=0; j<=i; j++)
            if (i==j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

void liberar_matriz(matriz m, int n) {
    int i;
    for (i=0; i<n; i++)
        free(m[i]);
    free(m);
}

void prim(matriz m, int nodos, cola *aristas) {
    /* calcular el árbol de recubrimiento mínimo devolviendo
       las aristas del arbol en la cola ’aristas’ */
    int min, i, j, k=0;
    arista a;
    int *masProximo = (int *) malloc(nodos*sizeof(int));
    int *distanciaMinima = (int *) malloc(nodos*sizeof(int));
    crear_cola(aristas);
    distanciaMinima[0] = -1;
    for(i = 1; i < nodos; i++) {
        masProximo[i] = 0;
        distanciaMinima[i] = m[i][0];
    }
/*
...
*/
    free(masProximo);
    free(distanciaMinima);
}
