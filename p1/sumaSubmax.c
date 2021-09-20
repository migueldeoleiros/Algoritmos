#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define N 5

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

void printResults (int v[]){
    printf("[ ");
    for (int i=0; i<N;i++){
        printf("%d ", v[i]);
    }
    printf("]");
    printf("    %d    %d \n", sumaSubMax1(v, N), sumaSubMax2(v, N));

}

double microsegundos() {  /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
return (t.tv_usec + t.tv_sec * 1000000.0);
}

int test3(int vector[]){
  int numero=500;
  float ta=0,tb=0,t=0;
  inicializar_semilla();
  aleatorio(vector,numero);
  ta=microsegundos();
  sumaSubMax1(vector);
  tb=microsegundos();
  t=tb-ta;
  if(t<500){
    float t1=0,t2=0;
    int k=500;
    ta=microsegundos();
    for(int i=0;i<k;i++){
      inicializar_semilla;
      aleatorio(vector,numero);
      sumaSubMax1(vector);
    }
    tb=microsegundos();
    t1=tb-ta;
    ta=microsegundos();
    for(int i=0;i<k;i++){
      inicializar_semilla;
      aleatorio(vector,numero);
    }
    tb=microsegundos();
    t2=tb-ta;
    t=(t1-t2)/k;
  }



}
int main() {

    int v[N] = {7,-5,6,7,-7};
    printResults(v);

// aleatorio

    inicializar_semilla();
    aleatorio(v, N);

    printResults(v);

    return 0;
}
