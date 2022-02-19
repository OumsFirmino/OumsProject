#include <stdio.h>
#include <stdlib.h>

void productVS(double **x,double tau, int n){

    for(int i = 0; i < n; i++){

        (*x)[i] = (*x)[i]*tau;
    }
}