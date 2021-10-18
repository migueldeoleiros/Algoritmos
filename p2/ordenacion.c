// TITLE: Algoritmos Práctica 1
// AUTHOR 1: Miguel López López        LOGIN 1: m.llopez
// AUTHOR 2: Ángel Gómez prol          LOGIN 2: angel.gomez.prol
// AUTHOR 3: Xoel Díaz Préstamo        LOGIN 3: xoel.diaz
// GROUP: 2.1.4
// DATE: 23/10/2021

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

void ord_sel(int v[],int n){
    int minj=0,minx=0;
    for(int i=0;i<n;i++){
        minj=i;
        minx=v[i];
        for(int j=i+1;j<n;j++){
            if(v[j]<minx){
    	    minj=j;
            minx=v[j];
            }
        }
        v[minj]=v[i];
        v[i]=minx;
    }
}

void ord_shell(int v[], int n){
    int tmp, j, seguir;
    int incremento = n;
    do{
        incremento /= 2;
        for(int i = incremento;i<n;i++){
			tmp=v[i];
            j=i; 
            seguir=1;
			while ((j-incremento>=0) && (seguir)){
				if (tmp<v[j-incremento]){
					v[j]=v[j-incremento];
					j-=incremento;
				}else seguir=0;
			}
			v[j]=tmp;
        }

    }while(incremento != 1);
}

double testAlgoritmo(int vector[], int numero, void (*func)(int[], int) ){
    double ta=0,tb=0,t=0;

    aleatorio(vector,numero);

    ta=microsegundos();
    func(vector, numero);
    tb=microsegundos();
    t=tb-ta;

    if(t<500){
        double t1=0,t2=0;
        int k=1000;

        ta=microsegundos();
        for(int i=0;i<k;i++){
            aleatorio(vector,numero);
            func(vector, numero);
        }
        tb=microsegundos();
        t1=tb-ta;

        ta=microsegundos();
        for(int i=0;i<k;i++){
            aleatorio(vector,numero);
        }
        tb=microsegundos();
        t2=tb-ta;
        t=(t1-t2)/k;
        printf("(*)");
    }else printf("   ");
    return t;
}

void printChart(void (*func)(int[], int) ){
    double t =0;
    double tsub, taj, tsob;

    printf("Test con SumaSubMax1 \n");
	printf("%7s%17s%20s%20s%19s \n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");

    for(int n = 500; n <= 32000; n*=2){
        int vector[n];
        t = testAlgoritmo(vector, n, func);

        tsub=t/pow(n,1.8);
		taj=t/pow(n,2);
		tsob=t/pow(n,2.2);
		printf("%6d%16.3f%18.6f%20.6f%18.6f\n", n, t, tsub, taj, tsob);
    }
}

void printVector(int v[], int n){
    printf("[");
    for (int i=0; i<n;i++){
        printf("%3d", v[i]);
    }
    printf(" ]\n");
}

void descendente(int v[], int n){
    int j=0;
    for(int i=n;i>0;i--) {
        j++;
        v[i-1]=j;
    }
}

void ascendente(int v[], int n){
    for(int i=0;i<n;i++) {
        v[i]=i;
    }
}

int main(){

    int n=10;
    int v[n];
    inicializar_semilla();

    aleatorio(v, n);
    printf("Inicializacion aleatoria\n");
    printVector(v, n);
    printf("Ordenacion por seleccion\n");
    ord_sel(v, n);
    printVector(v, n);

    printf("\n");

    printf("Inicializacion aleatoria\n");
    aleatorio(v, n);
    printVector(v, n);
    printf("Ordenacion por shell\n");
    ord_shell(v, n);
    printVector(v, n);

    printf("\n");

    descendente(v, n);
    printVector(v, n);
    printf("Ordenacion por seleccion\n");
    ord_sel(v, n);
    printVector(v, n);

    printf("\n");
    
    descendente(v, n);
    printVector(v, n);
    printf("Ordenacion por shell\n");
    ord_shell(v, n);
    printVector(v, n);

    printChart(ord_sel);
    printChart(ord_shell);
    return 0;
}