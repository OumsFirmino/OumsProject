#include <stdio.h>
#include <stdlib.h>
#include "residu.h"
#include "inversion.h"
#include "productMV.h"
#include "productVS.h"
#include "copie.h"
#include "add.h"

void conjugateGradient(double **dm_prev,double **rm_prev,double **b, double **xo,double **a, int **ja, int **ia, double **invl,int **jal,int **ial, int n, int *count, int maxit){

    
    double *rm;
    rm = malloc(n*sizeof(double));
    residu(b,a,ja,ia,xo,&rm,n);
    double *invBrm;
    invBrm = malloc(n*sizeof(double));
    productMV(invl,jal,ial,&rm,&invBrm,n);
    double *invBrm_prev;
    invBrm_prev = malloc(n*sizeof(double));
    productMV(invl,jal,ial,rm_prev,&invBrm_prev,n);
    
    double num = 0;
    double den = 0;

    for(int i = 0; i < n ; i++){
        num = num + rm[i]*invBrm[i];
        den = den + ((*rm_prev)[i])*(invBrm_prev[i]);   
    }
    double Bm = 0;
    if(den!=0){
            Bm = num/den;
    }

    double *dm;
    dm = malloc(n*sizeof(double));
    add(&invBrm,dm_prev,&dm,n,Bm);


    double *Adm;
    Adm = malloc(n*sizeof(double));
    productMV(a,ja,ia,&dm,&Adm,n);

    
    double den_alpha = 0;

    for(int i = 0; i< n;i++){

        den_alpha = den_alpha +dm[i]*Adm[i];

    }
    double alpha = num/den_alpha;
    add(xo,&dm,xo,n,alpha);
    *count = *count +1;
    if(*count < maxit){
    conjugateGradient(&dm,&rm,b,xo,a,ja,ia,invl,jal,ial,n,count,maxit);}
    








free(rm);free(invBrm_prev);free(invBrm);free(Adm);free(dm);











}