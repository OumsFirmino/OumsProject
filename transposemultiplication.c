#include <stdio.h>
#include <stdlib.h>

void transposemultiplication(double **ap,int **jp,int **ip, double **vc,double **result, int line_number){




// line_number  # ligne de la matrice initial





int line = 0;
int nnz = 0;
double alpha = 0.25;
while(line <line_number ){

    double coeff2 = (*vc)[line];


for(int i = (*ip)[line]; i< (*ip)[line +1]; i++){

double coeff1 = (*ap)[i];


(*result)[(*jp)[i]] = (*result)[(*jp)[i]] + alpha*coeff2*coeff1;
nnz++;


}

line++;

}






}