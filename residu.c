#include <stdio.h>
#include <stdlib.h>
#include "productMV.h"
#include "add.h"
#include "norme.h"
void residu(double **b, double**a,int **ja, int **ia, double **x, double **r, int n){

 
  double *Ax;
  Ax = malloc(n*sizeof(double));
  productMV(a,ja,ia,x,&Ax,n);
  for(int i = 0; i< n;i++){
    (*r)[i] = 0.0;
  }
  add(b,&Ax,r,n,-1);


  free(Ax);

}
