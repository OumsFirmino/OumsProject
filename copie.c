#include <stdio.h>
#include <stdlib.h>

void copie(double **a, double **b,int n){

        (*b)= malloc(n*sizeof(double));
        for(int i =0; i < n; i++){

            (*b)[i] = (*a)[i];
        }


}