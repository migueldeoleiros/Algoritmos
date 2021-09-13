#include <stdio.h>
 
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
 
 
 
    return 0;
}
