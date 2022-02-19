#include <stdio.h>
#include <stdlib.h>
#define A 1

double rho(int x, int y,int xR1d,int xR1f,int yR1d,int yR1f,int xR2d,int xR2f,int yR2d,int yR2f,double W){


    /*Coordonnées Radiateurs*( EPAISSEUR RADIATEUR = 20 CM)*/

    //Radiateur 1

    // représente une puissance cédée par le radiateur de 2kW
    double res=0;
if(A==1){
                
                 if(y>=yR1d && y<= yR1f){


                    if(x>=xR1d && x<=xR1f){

                    

                        res =W;}}

}

else if(A==2){
        if(y>=yR2d && y<= yR2f){


                    if(x>=xR2d && x<=xR2f){

                    

                        res =W;}}


}
else
{
    res = 0;
}

            

    return res;

   
    
    
    
    
   

   
    
}
