#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

int test3(int vector[], int numero){
  float ta=0,tb=0,t=0;

  inicializar_semilla(); aleatorio(vector,numero);

  ta=microsegundos();
  printf("%f\n", ta);
  sumaSubMax1(vector, numero);
  tb=microsegundos();
  printf("%f\n", tb);
  t=tb-ta;

  if(t<500){
    float t1=0,t2=0;
    int k=10000;

    ta=microsegundos();
    printf("%f\n", ta);
    for(int i=0;i<k;i++){
      inicializar_semilla(); aleatorio(vector,numero);
      sumaSubMax1(vector, numero);
    }
    tb=microsegundos();
    printf("%f\n", tb);
    t1=tb-ta;

    ta=microsegundos();
    for(int i=0;i<k;i++){
      inicializar_semilla(); aleatorio(vector,numero);
    }
    tb=microsegundos();
    t2=tb-ta;
    t=(t1-t2)/k;
  }
  return t;
}

int main() {
    int tiempo =0; 
    int n=5;

    int v[] = {7,-5,6,7,-7};
    printResults(v, n);

// aleatorio

    inicializar_semilla();
    aleatorio(v, n);

    printResults(v, n);

    n = 500;
    int vector[n];

    tiempo = test3(vector, n);

    printf("%d\n", tiempo);

    return 0;
}
