#include <stdio.h>
#include <stdlib.h>
/*
[P] = NxNc ou NC est le nombre d'inconnus de la coarse grid. Toujours prendre m-1 multiple de 20!



*/


void prolongation(int m,int n,int *nc,double **ap, int **jp, int **ip){

int mc =(m-1)/2 + 1;

int xP = 3*(m-1)/5;
int yP = 2*(m-1)/5;

int xPc = 3*(mc-1)/5;
int yPc = 3*(mc-1)/5;
*nc  = ((mc-2)*(yPc-1))+ (mc-2 -yPc+1)*(xPc-1);

(*ap) = malloc(9*(*nc)*sizeof(double));
(*jp) = malloc(9*(*nc)*sizeof(double));
(*ip) = malloc((n+1)*sizeof(int));



int nnz = 0;
int ind = 0;



for (int iy = 1; iy < yP ;iy++){

         
            for( int ix = 1; ix < m-1; ix++){

            ind = (ix -1) +(iy-1)*(m-2);
            (*ip)[ind] = nnz;

            // ix et iy pairs
            if(ix%2==0 && iy%2==0){

                (*ap)[nnz] = 1.0;
                (*jp)[nnz] = (iy/2 -1)*(mc-2) +(ix/2 -1);
                nnz++;
                  }
            
            // ix pair et iy impair

            if(ix%2==0 && iy%2!=0){

                if(iy ==1){

                    (*ap)[nnz] = 0.5;
                    (*jp)[nnz] = ix/2 - 1;
                    nnz++;
 
                }
                else if(iy== yP-1){
                    if(ix >= xP){

                            (*ap)[nnz] = 0.5;
                            (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + ix/2 - 1;
                            nnz++;

                    }
                    else{
                        // SUD
                            (*ap)[nnz] = 0.5;
                            (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + ix/2 - 1;
                            nnz++;
                        // NORD
                            (*ap)[nnz] = 0.5;
                            (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + ix/2 - 1;
                            nnz++;


                    }

                }
                else{

                    // SUD
                            (*ap)[nnz] = 0.5;
                            (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + ix/2 - 1;
                            nnz++;
                        // NORD
                            (*ap)[nnz] = 0.5;
                            (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + ix/2 - 1;
                            nnz++;

                }



            }
            // iy impair et ix pair
            if(ix%2!=0 && iy%2==0){

                if(ix==1){ //EST ONLY

                            (*ap)[nnz] = 0.5;
                            (*jp)[nnz] = ((iy)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                            nnz++;

                }

                else if(ix == (m-2)){    // WEST ONLY

                            (*ap)[nnz] = 0.5;
                            (*jp)[nnz] = ((iy)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                            nnz++;

                }
                else{

                    // WEST 
                            (*ap)[nnz] = 0.5;
                            (*jp)[nnz] = ((iy)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                            nnz++;

                    //EST 

                            (*ap)[nnz] = 0.5;
                            (*jp)[nnz] = ((iy)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                            nnz++;

                }




            }
            if(ix%2!=0 && iy%2!=0){

                if(iy==1){
                    if(ix==1){
                        // COIN S-D
                             (*ap)[nnz] = 0.25;
                            (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                            nnz++;

                    }
                    else if(ix==m-2){
                            // COIN S-G
                             (*ap)[nnz] = 0.25;
                            (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                            nnz++;

                    }
                    else{
                         // COIN S-D
                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;
                        // COIN S-G
                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;



                    }


                }

                else if(iy==yP -1){

                    if(ix == m-2){ // COIN I_G

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;

                    }
                    if(ix > xP && ix < m-2){
                        // COIN I_G

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;
                        
                        // COIN I_D

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;

                    }
                    if(ix == xP -1){
                         // COIN I_G

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;
                        
                        // COIN I_D

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;

                         // COIN S_G

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;


                    }
                    if(ix==1){

                        // COIN I_D

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;
                        // COIN S_D

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;


                    }

                    if(ix>1 && ix<xP-1){

                        // COIN I_G

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;
                        // COIN I_D

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;
                         // COIN S_G

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;
                         // COIN S_D

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;


                    }


                }
                else{

                    if(ix==1){
                            // COIN I_D

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;

                            // COIN S_D

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;

                    }

                    else if(ix ==m-2){

                        // COIN I_G

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;
                        // COIN S_G

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;

                    }

                    else{

                         // COIN I_G

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;
                        // COIN I_D

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy-1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;
                         // COIN S_G

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix-1)/2 - 1;
                             nnz++;
                         // COIN S_D

                             (*ap)[nnz] = 0.25;
                             (*jp)[nnz] = ((iy+1)/2 -1)*(mc-2) + (ix+1)/2 - 1;
                             nnz++;


                    }


                }


            }
           






              
              }





}
int indai = (yP/2 - 1)*(mc-2);
// ZONE 2

for(int iy = yP; iy < m-1; iy++){

    for(int ix = 1; ix < xP; ix++){

        ind = (yP -1)*(m-2) + (ix-1) + (iy-yP)*(xP -1);
        (*ip)[ind] = nnz;
        if(ix%2==0 && iy%2==0){

                (*ap)[nnz] = 1.0;
                (*jp)[nnz] = indai + ((iy-yP)/2)*(xP/2-1) +(ix/2 -1);
                nnz++;
                  }
        if(ix%2==0 && iy%2!=0){

            if(iy==m-2){
                (*ap)[nnz] = 0.5;
                (*jp)[nnz] = indai + ((iy-1-yP)/2)*(xP/2-1) +(ix/2 -1);
                nnz++;
            }
            else{
                (*ap)[nnz] = 0.5;
                (*jp)[nnz] = indai + ((iy-1-yP)/2)*(xP/2-1) +(ix/2 -1);
                nnz++;
                (*ap)[nnz] = 0.5;
                (*jp)[nnz] = indai + ((iy+1-yP)/2)*(xP/2-1) +(ix/2 -1);
                nnz++;

            }
        }
        if(ix%2!=0 && iy%2==0){
            if(ix==1){

                (*ap)[nnz] = 0.5;
                (*jp)[nnz] = indai + ((iy-yP)/2)*(xP/2-1) +((ix+1)/2 -1);
                nnz++;


            }
            else if(ix == xP-1){
                (*ap)[nnz] = 0.5;
                (*jp)[nnz] = indai + ((iy-yP)/2)*(xP/2-1) +((ix-1)/2 -1);
                nnz++;

            }
            else{

                 (*ap)[nnz] = 0.5;
                (*jp)[nnz] = indai + ((iy-yP)/2)*(xP/2-1) +((ix-1)/2 -1);
                nnz++;
                (*ap)[nnz] = 0.5;
                (*jp)[nnz] = indai + ((iy-yP)/2)*(xP/2-1) +((ix+1)/2 -1);
                nnz++;


            }

        }
    if(ix%2!=0 && iy%2!=0){

        if(ix==1){

            if(iy == m-2){

                 (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy-1-yP)/2)*(xP/2-1) +((ix+1)/2 -1);
                nnz++;

            }
            else{
                 (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy-1-yP)/2)*(xP/2-1) +((ix+1)/2 -1);
                nnz++;
                 (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy+1-yP)/2)*(xP/2-1) +((ix+1)/2 -1);
                nnz++;


            }

        }
        else if(ix == xP -1){
                if(iy == m-2){

                    (*ap)[nnz] = 0.25;
                    (*jp)[nnz] = indai + ((iy-1-yP)/2)*(xP/2-1) +((ix-1)/2 -1);
                    nnz++;

                }
                else{
                 (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy-1-yP)/2)*(xP/2-1) +((ix-1)/2 -1);
                nnz++;
                 (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy+1-yP)/2)*(xP/2-1) +((ix-1)/2 -1);
                nnz++;


            }



        }
        else{

            if(iy==m-2){
                (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy-1-yP)/2)*(xP/2-1) +((ix-1)/2 -1);
                nnz++;
                 (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy-1-yP)/2)*(xP/2-1) +((ix+1)/2 -1);
                nnz++;


            }
            else{
                (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy-1-yP)/2)*(xP/2-1) +((ix-1)/2 -1);
                nnz++;
                 (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy-1-yP)/2)*(xP/2-1) +((ix+1)/2 -1);
                nnz++;

                (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy+1-yP)/2)*(xP/2-1) +((ix-1)/2 -1);
                nnz++;
                 (*ap)[nnz] = 0.25;
                (*jp)[nnz] = indai + ((iy+1-yP)/2)*(xP/2-1) +((ix+1)/2 -1);
                
                nnz++;


            }


        }



    }


    }

}

(*ip)[ind+1] = nnz;




}


















