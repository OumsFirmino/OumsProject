#include <stdio.h>
#include <stdlib.h>

void printvec(double **a,int n){

    for(int i =0; i<n; i++ ){
        printf("vec(%d) = %e \n",i,(*a)[i]);
    }
}