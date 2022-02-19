//Calcul du flux à travers la fenere 
// j'utilise l'anologique electrique et la formule  phi = (deltaT*L)/R   ou deltaT = T2 - T1 T2 est la temperature au niveau de la partie intérieur de la fenetre et T1 la température  à l'extérieur de la feneretre!

#include <stdio.h>
#include <stdlib.h>

double flux(double R,int df,int ff, double h,int m, double **x,int dp,double Tf){

    double d = 0;

    double phi =0;


for(int i =df; i< ff+1;i++){
    
    d+= ((*x)[i] - Tf);

}

phi = (d*(ff-df)*h)/(R);



return  phi;









}