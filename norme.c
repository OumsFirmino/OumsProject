#include <math.h>
// permet de calculer la nrme d'une matrice colonne de taille n!
double norme(double **a, int n){
        double norme2 = 0.0;

        for(int i =0 ; i < n ; i++){

                norme2 = norme2 + ((*a)[i])*((*a)[i]);
        }

        double norm = sqrt(norme2);

    return norm; 
}
