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

int sumaSubMax1(int v[],int n)
{
    int sumaMax=0, estaSuma=0;

    for (int i = 0; i < n; i++) {
        estaSuma=0;
        for (int j = i; j < n; j++) {
            estaSuma=estaSuma+v[j];
            if (estaSuma>sumaMax)
                sumaMax=estaSuma;
        }
    }
    return sumaMax;
}

int sumaSubMax2 (int v[], int n){
    int estaSuma =0 , sumaMax =0;

    for (int j = 0; j<n; j++){
        estaSuma = estaSuma + v[j];
        if (estaSuma > sumaMax){
            sumaMax = estaSuma;
        }else if (estaSuma < 0){
            estaSuma = 0;
        }
    }
    return sumaMax;
}

void printResults (int v[], int n){
    printf("[");
    for (int i=0; i<n;i++){
        printf("%3d", v[i]);
    }
    printf("]");
    printf("%6d%6d \n", sumaSubMax1(v, n), sumaSubMax2(v, n));

}

void printTest1(){
    int n=5;
    int v[][5] = {
		{4,0,9,2,5},
		{-2,-1,-9,-7,-1},
		{9,-2,1,-7,-8},
		{7,-5,6,7,-7},
		{15,-2,-5,-4,16},
		{-9,2,-5,-4,6}
	};
 
    printf("test con vectores dados \n");
    for(int i=0; i<6;i++){
        printResults(v[i], n);
    }

}

void printAleatorio(){
    int n = 5;
    int vector[n];
    inicializar_semilla();
    aleatorio(vector, n);

    printf("Test con números aleatorios \n");
    printResults(vector, n);
}

double testSumaSubmax1(int vector[], int numero){
  double ta=0,tb=0,t=0;

  inicializar_semilla(); aleatorio(vector,numero);

  ta=microsegundos();
  sumaSubMax1(vector, numero);
  tb=microsegundos();
  t=tb-ta;

  if(t<500){
    double t1=0,t2=0;
    int k=1000;

    ta=microsegundos();
    for(int i=0;i<k;i++){
      inicializar_semilla(); aleatorio(vector,numero);
      sumaSubMax1(vector, numero);
    }
    tb=microsegundos();
    t1=tb-ta;

    ta=microsegundos();
    for(int i=0;i<k;i++){
      inicializar_semilla(); aleatorio(vector,numero);
    }
    tb=microsegundos();
    t2=tb-ta;
    t=(t1-t2)/k;
    printf("(*)");
  }else printf("   ");
  return t;
}

double testSumaSubmax2(int vector[], int numero){
  double ta=0,tb=0,t=0;

  inicializar_semilla(); aleatorio(vector,numero);

  ta=microsegundos();
  sumaSubMax2(vector, numero);
  tb=microsegundos();
  t=tb-ta;

  if(t<500){
    double t1=0,t2=0;
    int k=1000;

    ta=microsegundos();
    for(int i=0;i<k;i++){
      inicializar_semilla(); aleatorio(vector,numero);
      sumaSubMax2(vector, numero);
    }
    tb=microsegundos();
    t1=tb-ta;

    ta=microsegundos();
    for(int i=0;i<k;i++){
      inicializar_semilla(); aleatorio(vector,numero);
    }
    tb=microsegundos();
    t2=tb-ta;
    t=(t1-t2)/k;
    printf("(*)");
  }else printf("   ");
  return t;
}

void printsumasubmax1(){
    double t =0; 
    double tsub, taj, tsob;

    printf("Test con SumaSubMax1 \n");
	printf("%7s%17s%20s%20s%19s \n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");

    for(int n = 500; n <= 32000; n*=2){
        int vector[n];
        t = testSumaSubmax1(vector, n);

        tsub=t/pow(n,1.8);
		taj=t/pow(n,2);
		tsob=t/pow(n,2.2);
		printf("%6d%16.2f%18.6f%20.6f%18.6f\n", n, t, tsub, taj, tsob);
    }
}

void printsumasubmax2(){
    double t =0; 
    double tsub, taj, tsob;

    printf("Test con SumaSubMax2 \n");
	printf("%7s%17s%20s%20s%19s \n", "n", "t(n)", "t(n)/n^0.75", "t(n)/n^0.95", "t(n)/n^1.15");

    for(int n = 500; n <= 32000; n*=2){
        int vector[n];
        t = testSumaSubmax2(vector, n);

        tsub=t/pow(n,0.75);
		taj=t/pow(n,0.95);
		tsob=t/pow(n,1.15);
		printf("%6d%16.2f%18.6f%20.6f%18.6f\n", n, t, tsub, taj, tsob);
    }
}

int main() {

    //test con numeros dados
    printTest1();
    printf("\n");//separador

    // test con numeros aleatorios
    printAleatorio();
    printf("\n");//separador

    //tablas de tiempos
    printsumasubmax1();
    printf("\n");//separador
    printsumasubmax2();

    return 0;
}
