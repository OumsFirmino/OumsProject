#include <stdio.h>
#include <stdlib.h>
#include "norme.h"
#include "residu.h"
void stabilityCheck(double **x, double h,double **b,double **a, int **ja, int **ia,int m,int n){


    double norm_x = norme(x,n);
    double *r;
    r = malloc(n*sizeof(double));
    residu(b,a,ja,ia,x,&r,n);
    double norm_r = norme(&r,n);
    double l_max =  8/(h*h);
    
    double v  = (norm_r)/(norm_x*l_max);

    printf(" -------||r||/(||A||*||x||-------------) = %e", v);







}