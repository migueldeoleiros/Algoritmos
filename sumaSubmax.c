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
    int sumamax=0, estasuma=0;

    for (int i = 0; i < n; ++i) {
        estasuma=0;
        for (int j = i; j < n; ++j) {
            estasuma=estasuma+v[j];
            if (estasuma>sumamax)
                sumamax=estasuma;
        }
    }
    return sumamax;
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

int main() {
    int out1,out2;
    int v[N] = {7,-5,6,7,-7};
    out1 = sumaSubMax1(v, N);
    out2 = sumaSubMax2(v, N);

    printf("sumaSubMax1 = %d \n", out1);
    printf("sumaSubMax2 = %d \n \n", out2);
 
// aleatorio

    inicializar_semilla();
    aleatorio(v, N);

    out1 = sumaSubMax1(v, N);
    out2 = sumaSubMax2(v, N);

    for (int i=0; i<N;i++){
        printf("%d ", v[i]);
    }

    printf("sumaSubMax1 = %d \n", out1);
    printf("sumaSubMax2 = %d \n", out2);
 
    return 0;
}

