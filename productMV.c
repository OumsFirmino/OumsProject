#include <stdio.h>
#include <stdlib.h>
void productMV(double  **a, int  **ja,int **ia, double **x, double **reponse,int n ){

               for(int i = 0; i<n ; i++){
                       (*reponse)[i] = 0.0;
               }
	    

            double val ;

            for (int i = 0; i < n;i++){

                    val = 0.0;

                for( int j = (*ia)[i]; j < (*ia)[i+1]; j++){


                        val = val + ((*a)[j])*((*x)[(*ja)[j]]);


                }

                (*reponse)[i] = val;}
                

        
           

}
