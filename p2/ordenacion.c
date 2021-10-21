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
    int i,j;
    for(i=0;i<n;i++){
        minj=i;
        minx=v[i];
        for(j=i+1;j<n;j++){
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
    int tmp,j,i,seguir;
    int incremento = n;
    do{
        incremento /= 2;
        for(i = incremento;i<n;i++){
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

double testAlgoritmo(int vector[], int n, void (*func)(int[], int), void (*funGen)(int[], int)){
    double ta=0,tb=0,t=0,t1=0,t2=0;
    int k=1000;
    int count;

    funGen(vector,n);

    ta=microsegundos();
    func(vector, n);
    tb=microsegundos();
    t=tb-ta;

    if(t<500){

        ta=microsegundos();
        for(count=0;count<k;count++){
            funGen(vector,n);
            func(vector, n);
        }
        tb=microsegundos();
        t1=tb-ta;

        ta=microsegundos();
        for(count=0;count<k;count++){
            funGen(vector,n);
        }
        tb=microsegundos();
        t2=tb-ta;
        t=(t1-t2)/k;
        printf("(*)");
    }else printf("   ");
    return t;
}

void printChart(void (*func)(int[], int),void (*funGen)(int[], int),float cotaSub,float cotaAj,float cotaSob ){
    double t =0;
    double tsub, taj, tsob;
    int n;

    printf("\n");
	printf("%7s%16s%18s%.2f%15s%.2f%15s%.2f \n",
            "n", "t(n)", "t(n)/n^", cotaSub, "t(n)/n^", cotaAj, "t(n)/n^", cotaSob);

    for(n = 500; n <= 32000; n*=2){
        int vector[n];
        t = testAlgoritmo(vector, n, func, funGen);

        tsub=t/pow(n,cotaSub);
		taj=t/pow(n,cotaAj);
		tsob=t/pow(n,cotaSob);
		printf("%6d%16.3f%18.6f%20.6f%18.6f\n", n, t, tsub, taj, tsob);
    }
}

void printVector(int v[], int n){
    int i;
    printf("[");
    for (i=0; i<n;i++){
        printf("%3d", v[i]);
    }
    printf(" ]\n");
}

void descendente(int v[], int n){
    int i,j=0;
    for(i=n;i>0;i--) {
        j++;
        v[i-1]=j;
    }
}

void ascendente(int v[], int n){
    int i;
    for(i=0;i<n;i++) {
        v[i]=i;
    }
}
void testWithVector(void (*func)(int[], int),void (*funGen)(int[], int),int vector[],int  n){
    funGen(vector, n);
    printf("Input:\n");
    printVector(vector, n);
    printf("Output:\n");
    func(vector, n);
    printVector(vector, n);
}

int main(){
    int n=10;
    int v[n];
    inicializar_semilla();

    printf("Ordenacion por seleccion con vector aleatorio\n");
    testWithVector(ord_sel, aleatorio, v, n);
    printf("\n");

    printf("Ordenacion por seleccion con vector descendente\n");
    testWithVector(ord_sel, descendente, v, n);
    printf("\n");

    printf("Ordenacion por shell con vector aleatorio\n");
    testWithVector(ord_shell, aleatorio, v, n);
    printf("\n");

    printf("Ordenacion por shell con vector descendente\n");
    testWithVector(ord_shell, descendente, v, n);
    printf("\n");

    printChart(ord_shell,ascendente, 1,1.14,1.3);
    printChart(ord_shell,descendente, 1, 1.17, 1.3);
    printChart(ord_shell,aleatorio, 1, 1.19, 1.3);

    printChart(ord_sel,ascendente, 1.8, 2, 2.2);
    printChart(ord_sel,descendente, 1.8, 2, 2.2);
    printChart(ord_sel,aleatorio, 1.8, 1.98, 2.2);
    return 0;
}
