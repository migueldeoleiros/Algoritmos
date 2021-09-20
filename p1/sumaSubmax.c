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
    printf("[ ");
    for (int i=0; i<n;i++){
        printf("%d ", v[i]);
    }
    printf("]");
    printf("    %d    %d \n", sumaSubMax1(v, n), sumaSubMax2(v, n));

}

double microsegundos() {  /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
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
  }
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
  }
  return t;
}

int main() {
    double t =0; 
    int n=5;
    double tsub, taj, tsob;

    int v[] = {7,-5,6,7,-7};
    printResults(v, n);

// aleatorio

    inicializar_semilla();
    aleatorio(v, n);

    printResults(v, n);

    printf("Test con SumaSubMax1 \n");
	printf("%4s%19s%20s%21s%19s \n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
    n = 500;
    while(n <= 32000){
        int vector[n];
        t = testSumaSubmax1(vector, n);

        tsub=t/pow(n,1.8);
		taj=t/pow(n,2);
		tsob=t/pow(n,2.2);
		printf("%5d%17.2f%18.6f%22.6f%18.6f\n", n, t, tsub, taj, tsob);

        n*=2;
    }

    printf("Test con SumaSubMax2 \n");
	printf("%4s%19s%21s%22s%18s \n", "n", "t(n)", "t(n)/n^0.75", "t(n)/n^0.95", "t(n)/n^1.15");

    n = 500;
    while(n <= 32000){
        int vector[n];
        t = testSumaSubmax2(vector, n);

        tsub=t/pow(n,0.75);
		taj=t/pow(n,0.95);
		tsob=t/pow(n,1.15);
		printf("%5d%17.2f%18.6f%22.6f%18.6f\n", n, t, tsub, taj, tsob);


        n*=2;
    }


    return 0;
}
