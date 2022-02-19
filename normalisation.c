#include <stdio.h>
#include <stdlib.h>
#include "norme.h"

void normalisation(double **a, double **b,int  n){
        
    double facteur = norme(b,n);
    double alpha;
    for(int i = 0; i < n; i++){
       alpha  = (*a)[i]/facteur;
        (*a)[i] = alpha;
    }

}