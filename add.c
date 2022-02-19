//fonction qui permet de faire la différence entre les composantes de 2 matrices colones de taille n
#include <stdlib.h>
#include  <stdio.h>
int add(double **a, double **b,double **w, int n,double alpha){

       double *reponse;
    reponse = malloc(n*sizeof(double));

  for(int i = 0; i < n; i++){
        reponse[i] = 0.0;
    }

	 for(int i =0; i< n; i++){
                
                reponse[i] = (*a)[i] + ((*b)[i])*alpha;
        }
    for(int i = 1; i < n; i++){
        
        (*w)[i] = reponse[i];
    }

    free(reponse);
    return 0;
}
