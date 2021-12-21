// TITLE: Algoritmos Práctica 4
// AUTHOR 1: Miguel López López        LOGIN 1: m.llopez
// AUTHOR 2: Xoel Díaz Préstamo        LOGIN 3: xoel.diaz
// AUTHOR 3: Ángel Gómez prol          LOGIN 2: angel.gomez.prol
// GROUP: 2.1.4
// DATE: 07/12/2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>

#define TAM_MAX 8000
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

void inicializar_semilla(){
    srand(time(NULL));
}

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

void mostrar_cola(cola cola){
    int i;
    printf("\n --RESULTADO--\n");
    int pesoTotal=0;
    for(i=0;i<cola.final+1;i++){
        printf("(%d,",cola.vector[i].y);
        printf("%d)",cola.vector[i].x);
        pesoTotal+=cola.vector[i].peso;
    }
    printf("\n");
    printf("Peso: %d\n",pesoTotal);
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

void print_matriz(matriz m,int n) {
    int i,j;
    printf("\n --MATRIZ--\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
          printf(" %2d ",m[i][j]);
        }
      printf("\n");
    }
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
    for(i=1;i<nodos;i++){
        min=INT_MAX;
        for(j=1;j<nodos;j++){
            if(0<=distanciaMinima[j] && distanciaMinima[j]<min){
                min=distanciaMinima[j];
                k=j;
            }
        }
        a.x=k;
        a.y=masProximo[k];
        a.peso=m[k][masProximo[k]];
        insertar(a,aristas);
        distanciaMinima[k]=-1;
        for(j=1;j<nodos;j++){
            if(m[j][k]<distanciaMinima[j]){
                distanciaMinima[j]=m[j][k];
                masProximo[j]=k;
            }
        }
    }
    free(masProximo);
    free(distanciaMinima);
}

double tiemposAlgoritmo(void (*func)(matriz, int, cola*),void (*funGen)(matriz,int),
                        matriz matriz, int n, cola cola){
    double ta=0,tb=0,t=0,t1=0,t2=0;
    int k=1000;
    int count;

    funGen(matriz,n);

    ta=microsegundos();
    func(matriz, n, &cola);
    tb=microsegundos();
    t=tb-ta;

    if(t<500){

        ta=microsegundos();
        for(count=0;count<k;count++){
            funGen(matriz,n);
            func(matriz, n, &cola);
        }
        tb=microsegundos();
        t1=tb-ta;

        ta=microsegundos();
        for(count=0;count<k;count++){
            funGen(matriz,n);
        }
        tb=microsegundos();
        t2=tb-ta;
        t=(t1-t2)/k;
        printf("(*)");
    }else printf("   ");
    return t;
}

void printChart(void (*func)(matriz, int, cola*),void (*funGen)(matriz,int),
                float cotaSub,float cotaAj,float cotaSob ){
    double t=0;
    double tsub, taj, tsob;
    int n;
    matriz m= crear_matriz(320);
    cola *aristas = malloc(sizeof(cola));
    crear_cola(aristas);

    printf("\n");
    printf("%7s%16s%18s%.2f%15s%.2f%15s%.2f\n",
           "V", "t(V)", "t(V)/V^", cotaSub, "t(V)/V^", cotaAj, "t(V)/V^",
           cotaSob);

    for(n = 10; n <= 320 && t<500000; n*=2){
        t = tiemposAlgoritmo(func, funGen, m, n, *aristas);

        tsub=t/pow(n,cotaSub);
        taj=t/pow(n,cotaAj);
        tsob=t/pow(n,cotaSob);
        printf("%6d%16.3f%18.6f%20.6f%18.6f\n", n, t, tsub, taj, tsob);
    }
    liberar_matriz(m,320);
    free(aristas);
}

void testMatriz1(cola *aristas){
    int n=5,i,j;
    matriz m=crear_matriz(n);
    int a[5][5]={
        {0,1,8,4,7},
        {1,0,2,6,5},
        {8,2,0,9,5},
        {4,6,9,0,3},
        {7,5,5,3,0},
    };
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            m[i][j]=a[i][j];
    }

    print_matriz(m,n);
    prim(m,n,aristas);
    mostrar_cola(*aristas);
    liberar_matriz(m,n);
}

void testMatriz2(cola *aristas){
    int n=4,i,j;
    matriz m=crear_matriz(n);
    int a2[4][4]= {
        {0,1,4,7},
        {1,0,2,8},
        {4,2,0,3},
        {7,8,3,0},
    };
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            m[i][j]=a2[i][j];
    }

    print_matriz(m,n);
    prim(m,n,aristas);
    mostrar_cola(*aristas);
    liberar_matriz(m,n);
}
void testMatriz3(cola *aristas){
    int n=7,i,j;
    matriz m=crear_matriz(n);
    int a3[7][7]= {
        { 0, 7,99, 5,99,99,99},
        { 7, 0, 8, 9, 7,99,99},
        {99, 8, 0,99, 5,99,99},
        { 5, 9,99, 0,15, 6,99},
        {99, 7, 5,15, 0, 8, 9},
        {99,99,99, 6, 8, 0,11},
        {99,99,99,99, 9,11, 0}
    };
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            m[i][j]=a3[i][j];
    }

    print_matriz(m,n);
    prim(m,n,aristas);
    mostrar_cola(*aristas);
    liberar_matriz(m,n);
}

void testMatriz4(cola *aristas){
    int n=5;
    matriz m,x,y;
    m=crear_matriz(n);
    x=crear_matriz(n);
    y=crear_matriz(n);

    inicializar_matriz(m,n);
    inicializar_matriz(x,n);
    inicializar_matriz(y,n);

    print_matriz(m,n);
    prim(m,n,aristas);
    mostrar_cola(*aristas);
    liberar_matriz(m,n);

    print_matriz(x,n);
    prim(x,n,aristas);
    mostrar_cola(*aristas);
    liberar_matriz(x,n);

    print_matriz(y,n);
    prim(y,n,aristas);
    mostrar_cola(*aristas);
    liberar_matriz(y,n);
}

int main(){
    cola *aristas = malloc(sizeof(cola));
    inicializar_semilla();
    crear_cola(aristas);
    testMatriz1(aristas);
    testMatriz2(aristas);
    testMatriz3(aristas);
    testMatriz4(aristas);
    printChart(prim,inicializar_matriz,1.5,1.8,2);
    free(aristas);
}
