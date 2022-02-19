#define v 1
#include "inversion.h"
#include "productMV.h"
#include "add.h"
#include "residu.h"
#include <stdlib.h>
#include <stdio.h>
#include "norme.h"
#include "printvec.h"
#include "normalisation.h"
#include "productVS.h"

void smoothing(double **b, double **xo,double **a, int **ja, int **ia, double **invl,int **jal,int **ial, int n,double tau){
    
    double *ro;
    ro = malloc(n*sizeof(double));
    residu(b,a,ja,ia,xo,&ro,n);
    double *dm;
    dm =malloc(n*sizeof(double));
    productVS(&dm,tau,n);
    productMV(invl,jal,ial,&ro,&dm,n);
    add(xo,&dm,xo,n,1); 
    
    free(dm); free(ro);

}
