#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double convergenceFactor(double lnr, int mrho, double ro,double *tau,double *l_min,double *l_max,int cas){


    printf("mrho = %d  lnr = %e  ro = %en\n",mrho,lnr,ro);
    double lnrro = lnr  - log(ro);
    double lnrho = lnrro/mrho;

    double convergenceFactor = exp(lnrho);

  printf("début stagnation m = %d et lnr = %e\n",mrho,lnr);

  if(cas==1){
  *l_min = 1 -convergenceFactor;
  *tau = 1+convergenceFactor;

  }
  if(cas==2){

    *tau = (1-convergenceFactor)/(*l_min);
  }




    return convergenceFactor;

}