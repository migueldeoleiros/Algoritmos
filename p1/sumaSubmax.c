// TITLE: Algoritmos Práctica 1
// AUTHOR 1: Miguel López López        LOGIN 1: m.llopez
// AUTHOR 2: Ángel Gómez prol          LOGIN 2: angel.gomez.prol
// AUTHOR 3: Xoel Díaz Préstamo        LOGIN 3: xoel.diaz
// GROUP: 2.1.4
// DATE: 20/09/2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

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

int sumaSubMax1(int v[],int n){
    int sumaMax=0, estaSuma=0;
    int i,j;

    for (i = 0; i < n; i++) {
        estaSuma=0;
        for (j = i; j < n; j++) {
            estaSuma=estaSuma+v[j];
            if (estaSuma>sumaMax)
                sumaMax=estaSuma;
        }
    }
    return sumaMax;
}

int sumaSubMax2 (int v[], int n){
    int i, estaSuma =0 , sumaMax =0;

    for (i = 0; i<n; i++){
        estaSuma = estaSuma + v[i];
        if (estaSuma > sumaMax){
            sumaMax = estaSuma;
        }else if (estaSuma < 0){
            estaSuma = 0;
        }
    }
    return sumaMax;
}

void printResults (int v[], int n){
    int i;
    printf("[");
    for (i=0; i<n;i++){
        printf("%3d", v[i]);
    }
    printf("]");
    printf("%6d%6d \n", sumaSubMax1(v, n), sumaSubMax2(v, n));

}

void printTest1(){
    int i,n=5;
    int v[][5] = {
		{4,0,9,2,5},
		{-2,-1,-9,-7,-1},
		{9,-2,1,-7,-8},
		{7,-5,6,7,-7},
		{15,-2,-5,-4,16},
		{-9,2,-5,-4,6}
	};

    for(i=0; i<6;i++){
        printResults(v[i], n);
    }

}

void printAleatorio(){
    int n = 5;
    int vector[n];
    aleatorio(vector, n);

    printResults(vector, n);
}

double tiemposAlgoritmo(int vector[], int n, int (*func)(int[], int)
                        , void (*funGen)(int[], int)){
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

void printChart(int (*func)(int[], int),void (*funGen)(int[], int)
                ,float cotaSub,float cotaAj,float cotaSob ){
    double t =0;
    double tsub, taj, tsob;
    int n;
    int vector[32000];

    printf("\n");
    printf("%7s%16s%18s%.2f%15s%.2f%15s%.2f \n",
            "n", "t(n)", "t(n)/n^", cotaSub, "t(n)/n^", cotaAj, "t(n)/n^", cotaSob);

    t=0;
    for(n = 500; n <= 32000; n*=2){
        t = tiemposAlgoritmo(vector, n, func, funGen);

        tsub=t/pow(n,cotaSub);
        taj=t/pow(n,cotaAj);
        tsob=t/pow(n,cotaSob);
        printf("%6d%16.3f%18.6f%20.6f%18.6f\n", n, t, tsub, taj, tsob);
    }
}


int main() {
    int i;
    inicializar_semilla(); 
    //test con numeros dados
    printf("Test con vectores dados\n");
    printTest1();
    printf("\n");//separador

    // test con numeros aleatorios
    printf("Test con números aleatorios\n");
    for(i=0;i<6;i++)
      printAleatorio();
    printf("\n");//separador

    //tablas de tiempos
    printf("Test con sumaSubMax1\n");
    printChart(sumaSubMax1,aleatorio,1.8,2,2.2);
    printf("\n");
    printf("Test con sumaSubMax2\n");
    printChart(sumaSubMax2,aleatorio,0.75,0.95,1.15);

    return 0;
}
