#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main() {

    int v[N] = {7,-5,6,7,-7};
    printResults(v);

// aleatorio

    inicializar_semilla();
    aleatorio(v, N);

    printResults(v);
 
    return 0;
}

