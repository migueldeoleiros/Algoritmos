#include <stdio.h>

#define N 5
 
int sumaSubMax1(int v[],int n)
{
    int sumamax=0;
    for (int i = 0; i < n; ++i) {
        int estasuma=0;
        for (int j = 0; j < n; ++j) {
            estasuma=estasuma+v[j];
            if (estasuma>sumamax)
                sumamax=estasuma;
        }
    }
    return sumamax;
}

int sumaSubMax2 (int v[], int n){
    int estaSuma, sumaMax =0;

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
    int v[N] = {4,0,9,2,5};
    out1 = sumaSubMax1(v, N);
    out2 = sumaSubMax2(v, N);
 
 
    return 0;
}

