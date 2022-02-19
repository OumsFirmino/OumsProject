#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prob.h"
#include "umfpk.h"
#include "time.h"
#include "temperature.h"
#include "plotTemperature.h"
#include "rho.h"
#include "flux.h"
#include "residu.h"
#include "norme.h"
#include "LU.h"
#include "smoothing.h"
#include <assert.h>
#include "inversion.h"
#include "printvec.h"
#include "normalisation.h"
#include "transposemultiplication.h"
#include "productMV.h"
#include "add.h"
#include "prolongation.h"
#include "Rinjection.h"
#include "math.h"
#include "copie.h"
#include "Vcycle.h"
#include "RFW.h"
#include "twogrid.h"
#include "stabilityCheck.h"
#include "convergenceFactor.h"
#include "cGVcycle.h"
double (*func)(int, int , int , int,int,int,int,int,int,int,double);
double (*func2)(int,int,int,int,int,int,int,double**,double);



/* Fonction main */

int main(int argc, char *argv[])
{
/* déclarer les variables */
int m =641;
/*longueur de la pièce*/
int L = 5;
double h = L/(float)(m-1);
/*indice porte*/
int  dp = (m-1)/(2*L);
int fp = (3*(m-1))/(2*L);
 /*indice fenetre*/
    int df = (3*(m-1))/(2*L);
    int ff = (7*(m-1))/(2*L);
/*coordonnées du point de coupure */
    int xP = (3*(m-1))/L;
    int yP = (2*(m-1))/L ;
/*paramètres physiques*/

double Tp = 20;
double Tf = 0.0;
double R = 0.17;
double Wt= 60; // represente la puissance du radiateur multiplié par la surface de ce dernier !
int n,*ia, *ja,*jal,*ial,*jau,*iau;
double *a, *b, *x,*al,*au;
 double t1, t2;
func = &rho;
FILE *variance;
variance = fopen("variance.txt","w");
func2 = &temperature;
int nnz_tr;


printf("\n\n----------Modifier la valeur de A dans rho.c pour changer de problème---------\n\n");

 /* générér le problème */

  if (prob(m, &n, &ia, &ja, &a, &b,&al,&jal,&ial,&au,&jau,&iau,func,&nnz_tr))
     return 1;
  printf("\nPROBLEM: ");
  printf("m = %5d   n = %8d  nnz = %9d\n", m, n, ia[n] );



  /* allouer la mémoire pour le vecteur de solution  */

  x = malloc(n * sizeof(double));
  if ( x == NULL ) {
  	printf("\n ERREUR : pas de mémoire pour vecteur des solutions\n\n");
        return 1;

  }
 

  /* résoudre et mesurer le temps de solution */

 t1 = mytimer();
  if( solve_umfpack(n, ia, ja, a, b, x) )
     return 1;
  t2 = mytimer();


 printf("\nTemps de solution (CPU): %5.1f sec\n",t2-t1);


  /* Partie consacrée au calcul de résidu*/
    printf("\nLa variance est égale à:  %e pour Wt = %f\n" ,temperature(dp,fp,df,ff,xP,yP,m,&x,Tp),Wt);
   printf("\nLa dispotion A = 1 du radiateur est celle qui mène à une distribution plus uniforme de la température car la variance est plus petite !\n");
   printf("\nLa Puissance du radiateur qui mène à une distribution plus uniforme est Wt = 60 ce qui implique une puissance de 150W/m² \n");
   printf("\nLe flux linéique est plus grand que la puissance du radiateur mais il faudrait encore le diviser par la hauteur de la fenetre!\n");
   fprintf(variance, "%f\n",temperature(dp,fp,df,ff,xP,yP,m,&x,Tp));
   plotTemperature();
   printf("\nLe flux linéïque de chaleur a travers la fênetre est de : %f  Watt/m\n", flux(R,df,ff,h,m,&x,dp,Tf));
   fclose(variance);



// FICHIER POUR COMPARER 2 GRID ET MULTIGRID
double *r;
r = malloc(n*sizeof(double));
residu(&b,&a,&ja,&ia,&x,&r,n);
double lnr = 0;
int mrho = 0;
double ro = norme(&r,n)/norme(&b,n);
int stop = 0;
double tau = 1;
double l_min;
double l_max;


 printf("\n\n------------------------------2-GRID METHOD and V-cycle (L = 4) comparaison with symmetrized-GS --------------------------\n\n");

 // residu solution initiale
FILE *comparaison;
comparaison = fopen("q3.txt","w");
double *xt;
copie(&x,&xt,n);
double *xm;
copie(&x,&xm,n);
for(int i = 0 ; i < n; i++){
	
		xt[i]= 0.0;
		xm[i] = 0.0;
}
FILE *ft;
ft= fopen("ft.txt","w");
double *rt;
rt = malloc(n*sizeof(double));
residu(&b,&a,&ja,&ia,&xt,&rt,n);
double *rm;
rm = malloc(n*sizeof(double));
residu(&b,&a,&ja,&ia,&xm,&rm,n);
fprintf(comparaison,"%d %e %e\n",0,norme(&rt,n)/norme(&b,n),norme(&rm,n)/norme(&b,n));
FILE *fm;
fm = fopen("fm.txt","w");




int itt = 0;
while(itt < 15){

twogrid(&xt,&b,&a,&ja,&ia,&au,&jau,&iau,&al,&jal,&ial,m,n,nnz_tr,itt,ft,tau);
int countv = 0;
int Level = 3;
double rpre = norme(&rm,n)/norme(&b,n);
Vcycle(&xm,&b,&a,&ja,&ia,&au,&jau,&iau,&al,&jal,&ial,m,n,nnz_tr,Level,&countv,itt,fm,1);
residu(&b,&a,&ja,&ia,&xt,&rt,n);
residu(&b,&a,&ja,&ia,&xm,&rm,n);
fprintf(comparaison,"%d %e %e\n",itt+1,norme(&rt,n)/norme(&b,n),norme(&rm,n)/norme(&b,n));
itt++;
double r1 = norme(&rm,n)/norme(&b,n);
if(stop==0){

double arret = fabs((r1 - rpre)/rpre);


if(arret< 0.01){
   mrho = itt;
   lnr  = log(r1);
   stop = 1;
   
}


}



}
stabilityCheck(&xm, h,&b,&a, &ja, &ia,m, n);

printf("Le Facteur de Convergence est égale à : %e\n",convergenceFactor(lnr,mrho,ro,&tau,&l_min,&l_max,1));
printf("Le coeffecient de relaxation Tau = %e\n", tau);



printf("\n\n------------------------------ VCYCLE MULTIGRID METHOD ACCELERATED with Symmetrized-GS Tau = %e--------------------------\n\n",tau);

double *xma;
copie(&x,&xma,n);



FILE *mgaccelerated;
mgaccelerated = fopen("mgaccelerated.txt","w");
FILE *fmga;
fmga = fopen("fmga.txt","w");

double *rma;
rma = malloc(n*sizeof(double));
residu(&b,&a,&ja,&ia,&xma,&rma,n);
fprintf(mgaccelerated,"%d %e \n",0,norme(&rma,n)/norme(&b,n));
double romga = norme(&rma,n)/norme(&b,n);
stop = 0;

int itt2 = 0;
while(itt2 < 15){

int countv = 0;
int Level = 3;
double rpremga = norme(&rm,n)/norme(&b,n);
Vcycle(&xma,&b,&a,&ja,&ia,&au,&jau,&iau,&al,&jal,&ial,m,n,nnz_tr,Level,&countv,itt2,fmga,tau);
residu(&b,&a,&ja,&ia,&xma,&rma,n);
double rmga = norme(&rma,n)/norme(&b,n);
fprintf(mgaccelerated,"%d %e \n",itt2+1,rmga);

if(stop==0){

double arret = fabs((rmga - rpremga)/rpremga);


if(arret< 0.01){
   mrho = itt;
   lnr  = log(rmga);
   stop = 1;
   
}



}
itt2++;}




printf("Asymptotic Convergence Factor of accelerated MG = %e  \n",convergenceFactor(lnr,mrho,romga,&tau,&l_min,&l_max,2));
printf("Optimal relexation factor = %e\n",tau);

printf("\n\n------------------------------ VCYCLE MULTIGRID METHOD ACCELERATED with Symmetrized-GSCorrected Tau = %e--------------------------\n\n",tau);
double *xmac;
copie(&x,&xmac,n);
FILE *mgacceleratedcorrected;
mgacceleratedcorrected= fopen("mgacceleratedcorrected.txt","w");
FILE *fmgac;
fmgac = fopen("fmgac.txt","w");

double *rmac;
rmac = malloc(n*sizeof(double));
residu(&b,&a,&ja,&ia,&xmac,&rmac,n);
fprintf(mgacceleratedcorrected,"%d %e \n",0,norme(&rmac,n)/norme(&b,n));

int itt3 = 0;



while(itt3 < 15){

int countv = 0;
int Level = 3;

Vcycle(&xmac,&b,&a,&ja,&ia,&au,&jau,&iau,&al,&jal,&ial,m,n,nnz_tr,Level,&countv,itt3,fmgac,tau);
residu(&b,&a,&ja,&ia,&xmac,&rmac,n);
double rmgac = norme(&rmac,n)/norme(&b,n);
fprintf(mgacceleratedcorrected,"%d %e \n",itt3+1,rmgac);

itt3++;}

printf("\n\n------------------------------ VCYCLE MULTIGRID METHOD ACCELERATED with ConjugateGradient smoother--------------------------\n\n");


double *xcg;
copie(&x,&xcg,n);
FILE *cg;
cg= fopen("cg.txt","w");
FILE *fcg;
fcg = fopen("fcg.txt","w");

double *rcg;
rcg = malloc(n*sizeof(double));
residu(&b,&a,&ja,&ia,&xcg,&rcg,n);
fprintf(cg,"%d %e \n",0,norme(&rcg,n)/norme(&b,n));

int itt4 = 0;



while(itt4 < 15){

int countv = 0;
int Level = 3;

cGVcycle(&xcg,&b,&a,&ja,&ia,&au,&jau,&iau,&al,&jal,&ial,m,n,nnz_tr,Level,&countv,itt3,fcg,tau);
residu(&b,&a,&ja,&ia,&xcg,&rcg,n);
double rescg = norme(&rcg,n)/norme(&b,n);
fprintf(cg,"%d %e \n",itt4+1,rescg);

itt4++;}





  /* libéré la mémoire */

free(ia); free(ja); free(a); free(b); free(x); free(r);
free(ial);free(jal);free(al);free(iau);free(jau);free(au);
free(xm);free(xt);
fclose(ft);
fclose(fm);
fclose(comparaison);
fclose(fcg);
fclose(cg);



  

  return 0;
}
