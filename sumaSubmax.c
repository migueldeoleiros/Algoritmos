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


//////////////////////////////////////////////////


    void sumaSubMax1(int pepe[],int n)
    {
        int sumamax=0;
        for (int i = 1; i < n; ++i) {
            int estasuma=0;
            for (int j = 1; j < n; ++j) {
                estasuma=estasuma+n;
                if (estasuma>sumamax)
                    sumamax=estasuma;
            }
        }
    }
    int main (void)
    {
     
     
       return 0;
    }
