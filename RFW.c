#include <stdio.h>
#include <stdlib.h>



void RFW(double **ar, int **jr, int **ir, int m, int *nc){




int mc = (m-1)/2 +1 ; // nombre de points coarse sur une ligne horizon de longueur 5
int xPc = (3*(mc-1)/5);
int yPc = (2*(mc-1)/5);
*nc = ((mc-2)*(yPc-1))+ (mc-2 -yPc+1)*(xPc-1);



int nnz = 9*(*nc);



(*ar) = malloc(nnz*sizeof(double));
(*jr) = malloc(nnz*sizeof(int));
(*ir) = malloc((*nc+1)*sizeof(int));



int xP = (3*(m-1)/5);
int yP = (2*(m-1)/5);
nnz = 0;
int ind = 0;
int inda = 0;





// ZONE 1


  for (int iy = 1; iy < yP ;iy++){

          if(iy%2==0){
            for( int ix = 1; ix < m-1; ix++){


              if(ix%2==0){
                inda = (ix -1) +(iy-1)*(m-2);
                (*ir)[ind] = nnz;


              // coeff sud -est


                (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] = inda - (m-2) -1;
                nnz++;

            // coeff sud
                    (*ar)[nnz] = 1.0/14;
                    (*jr)[nnz] = inda - (m-2) ;
                    nnz++;

            // coeff sud-west

                         (*ar)[nnz] = 1.0/14;
                        (*jr)[nnz] = inda - (m-2)  +1;
                        nnz++;


              // coeff west:


                (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] = inda  -1;
                nnz++;




              // coeff Diag

              (*ar)[nnz] = 6/14;
              (*jr)[nnz] = inda;
              nnz++;



              // coeff E



                (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] = inda  +1;
                nnz++;




              // coeff-  nord -ouest

                  (*ar)[nnz] = 1.0/14;
                  (*jr)[nnz] = inda + (m-2) -1;
                  nnz++;


            // coeff -nord

                      (*ar)[nnz] = 1.0/14;
                  (*jr)[nnz] = inda + (m-2) ;
                  nnz++;


            // coeff nord-est

                (*ar)[nnz] = 1.0/14;
                  (*jr)[nnz] = inda + (m-2) +1 ;
                  nnz++;



              ind++;
              }





            }

        }
}

// DEBUT ZONE 2



        for(int iy = yP; iy < m-1 ; iy ++){
          if(iy%2==0){

            for(int ix = 1; ix < xP; ix ++){

              if(ix%2==0){
              inda = (yP -1)*(m-2) + (ix-1) + (iy-yP)*(xP -1);
              (*ir)[ind] = nnz;

              // coeff  sud
              if(iy==yP){


                (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] = inda - (m-2) -1 ;
                nnz++;
                (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] = inda - (m-2)  ;
                nnz++;
                 (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] = inda - (m-2) +1 ;
                nnz++;



              }
              else{

                (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] =inda - (xP - 1)  -1;
                nnz++;
                (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] =inda - (xP - 1) ;
                nnz++;
                 (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] =inda - (xP - 1)  +1;
                nnz++;
              }

              // Coeff Ouest

             (*ar)[nnz] = 1.0/14;
              (*jr)[nnz] =inda -1;
              nnz++;



              // Coeff Diagonal
              (*ar)[nnz] = 6.0/14;
              (*jr)[nnz] =inda;
              nnz++;


            // coeff est

                (*ar)[nnz] = 1.0/14;
              (*jr)[nnz] =inda +1;
              nnz++;

             
              // Coeff nord

              (*ar)[nnz] = 1.0/14;
              (*jr)[nnz] =inda + (xP - 1) -1 ;
              nnz++;

                (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] =inda + (xP - 1) ;
                nnz++;

                (*ar)[nnz] = 1.0/14;
                (*jr)[nnz] =inda + (xP - 1) +1 ;
                nnz++;










          ind++;

    }
  }
}
} // FIN ZONE 2


(*ir)[ind] = nnz;







      }