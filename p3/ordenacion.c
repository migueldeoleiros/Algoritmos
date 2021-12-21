// TITLE: Algoritmos Práctica 3
// AUTHOR 1: Miguel López López        LOGIN 1: m.llopez
// AUTHOR 2: Xoel Díaz Préstamo        LOGIN 3: xoel.diaz
// AUTHOR 3: Ángel Gómez prol          LOGIN 2: angel.gomez.prol
// GROUP: 2.1.4
// DATE: 20/1 /2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#define UMBRAL 1

void inicializar_semilla(){
    srand(time(NULL));
}

void aleatorio(int v[], int n){
    int i, m=2*n+1;
    for (i=0;i<n;i++){
        v[i] = (rand() % m) - n;
    }
}

double microsegundos() {  /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void ordenacionPorInsercion(int v[],int n){
    int x=0,i=0,j=0;
    for(i=1;i<n;i++){
        x=v[i];
        j=i-1;
        while(j>-1 && v[j]>x){
            v[j+1]=v[j];
            j=j-1;
        }
        v[j+1]=x;
    }
}
void intercambiar(int *a, int *b){
    int aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

void mediana3(int v[],int i,int j){
    int k;
    k=(i+j)/2;
    if(v[k]>v[j]) intercambiar(&v[k],&v[j]);
    if(v[k]>v[i]) intercambiar(&v[k],&v[i]);
    if(v[i]>v[j]) intercambiar(&v[i],&v[j]);
}

void ordenarAux(int v[],int izq,int der){
    int pivote=0,i=0,j=0;
    if((izq+UMBRAL)<=der){
        mediana3(v,izq,der);
        pivote= v[izq];
        i=izq;
        j=der;
        do{
            do{
                i++;
            }while(v[i]<pivote);
            do{
                j--;
            }while (v[j]>pivote);
            intercambiar(&v[i],&v[j]);
        }while(j>i);
        intercambiar(&v[i],&v[j]);
        intercambiar(&v[izq],&v[j]);
        ordenarAux(v,izq,j-1);
        ordenarAux(v,j+1,der);
    }
}

void quicksort(int v[],int n){
    ordenarAux(v,0,n-1);
    if(UMBRAL>1)
        ordenacionPorInsercion(v,n);
}

double tiemposAlgoritmo(int vector[], int n, void (*func)(int[], int),
                        void (*funGen)(int[], int)){
    double ta=0,tb=0,t=0,t1=0,t2=0;
    int k=1000;
    int count;

    funGen(vector,n);

    ta=microsegundos();
    func(vector, n);
    tb=microsegundos();
    t=tb-ta;

    if(t<500){
        ta=microsegundos();
        for(count=0;count<k;count++){
            funGen(vector,n);
            func(vector, n);
        }
        tb=microsegundos();
        t1=tb-ta;

        ta=microsegundos();
        for(count=0;count<k;count++){
            funGen(vector,n);
        }
        tb=microsegundos();
        t2=tb-ta;
        t=(t1-t2)/k;
        printf("(*)");
    }else printf("   ");
    return t;
}

void printChart(void (*func)(int[], int),void (*funGen)(int[], int),
                float cotaSub,float cotaAj,float cotaSob ){
    double t =0;
    double tsub, taj, tsob;
    int n;
    int vector[128000];

    printf("\n");
    printf("%7s%16s%18s%.2f%15s%.2f%15s%.2f \n",
            "n", "t(n)", "t(n)/n^", cotaSub, "t(n)/n^", cotaAj, "t(n)/n^", cotaSob);

    t=0;
    for(n = 500; n <= 128000 && t<500000; n*=2){
        t = tiemposAlgoritmo(vector, n, func, funGen);

        tsub=t/pow(n,cotaSub);
        taj=t/pow(n,cotaAj);
        tsob=t/pow(n,cotaSob);
        printf("%6d%16.3f%18.6f%20.6f%18.6f\n", n, t, tsub, taj, tsob);
    }
}

void printVector(int v[], int n){
    int i;
    printf("[");
    for (i=0; i<n;i++){
        printf("%3d", v[i]);
    }
    printf(" ]\n");
}

void descendente(int v[], int n){
    int i,j=0;
    for(i=n;i>0;i--) {
        j++;
        v[i-1]=j;
    }
}

void ascendente(int v[], int n){
    int i;
    for(i=0;i<n;i++) {
        v[i]=i;
    }
}

void testWithVector(void (*func)(int[], int),void (*funGen)(int[], int),
                    int vector[],int  n){
    funGen(vector, n);
    printf("Input: ");
    printVector(vector, n);
    printf("Output:");
    func(vector, n);
    printVector(vector, n);
}

void printearTestAleatorios(void (*func)(int[],int),int vector[],int n){
    int i;
    for(i=0;i<4;i++){
        testWithVector(func, aleatorio, vector, n);
        printf("\n");
    }
}

void printearAscenDescen(void (*func)(int[],int),int vector[],int n){
    testWithVector(func, descendente, vector, n);
    printf("\n");
    testWithVector(func,ascendente,vector,n);
    printf("\n");

}

int main(){
    int n=10,v[n];
    inicializar_semilla();

    printf("\n%8s ORDENACION POR INSERCION \n","");
    printearTestAleatorios(ordenacionPorInsercion,v,n);
    printearAscenDescen(ordenacionPorInsercion,v,n);
    printf("%8s***---------------***\n","");
    printf("%13s QUICKSORT \n","");
    printearTestAleatorios(quicksort,v,n);
    printearAscenDescen(quicksort,v,n);

    printf("\nOrdenacion por insercion de vector ascendente:");
    printChart(ordenacionPorInsercion,ascendente, 0.85, 1, 1.2);
    printf("\nOrdenacion por insercion de vector descendente:");
    printChart(ordenacionPorInsercion,descendente, 1.8, 2, 2.2);
    printf("\nOrdenacion por insercion de vector aleatorio:");
    printChart(ordenacionPorInsercion,aleatorio, 1.8, 1.98, 2.2);

    printf("\nOrdenacion por quicksort de vector ascendente:");
    printChart(quicksort,ascendente,0.8,1.08,1.6);
    printf("\nOrdenacion por quicksort de vector descendente:");
    printChart(quicksort,descendente,0.8,1.09,1.6);
    printf("\nOrdenacion por quicksort de vector aleatorio:");
    printChart(quicksort,aleatorio,0.8,1.1,1.6);
}
