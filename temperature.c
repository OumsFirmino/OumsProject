#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int ind=0;



//fonction qui permet d'écrire dans le fichier file et de calculer la variance !

double temperature(int dp,int fip, int df, int ff,int xP, int yP,int m,double **sol,double Tp){

  FILE * file;
  file = fopen("file.txt", "w");


  double variance =0;

  double T2 = 0;
  double T =0;
  int count = 0;

  double h  = 5/(float)(m-1);
  
    
    

    /*ZONE 1*/
     for (int iy = 1; iy < yP ;iy++){ // on s'arrete à  Y = 2 compris 

        for( int ix = 1; ix < m-1; ix++){ 



            ind = (ix-1) + (iy -1)*(m-2);
            fprintf(file, "%f %f %f\n",ix*h,iy*h,(*sol)[ind]);
            
                 T+= (*sol)[ind];
                 T2+= ((*sol)[ind])*((*sol)[ind]);
                count++;
            

             }}


    /*ZONE2*/

  for(int iy = yP; iy < m-1 ; iy ++){

            for(int ix = 1; ix < xP; ix ++){

            ind = (yP -1)*(m-2) + (ix-1) + (iy-yP)*(xP -1);
            fprintf(file, "%f %f %f\n",ix*h,iy*h,(*sol)[ind]);
                T+= (*sol)[ind];
                 T2+= ((*sol)[ind])*((*sol)[ind]);
                count++;

               
        }}


    
    



    variance = T2/count - (T/count)*(T/count);
   
    fclose(file);

    return variance;
   
    
  
    }

     




















