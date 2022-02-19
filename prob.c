#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rho.h"

// Problème dans la fonction rho à corriger et faire attention à température 2 !!!

int prob(int m, int *n, int **ia, int **ja, double **a, double **b,double **al,int **jal,int **ial,double **au,int **jau,int **iau,double (*rho)(int,int,int,int,int,int,int,int,int,int,double),int *nnz_tr){
/*
   But
   ===
   Générer le système linéaire n x n

                             Au = b

   qui correspond à la discrétisation sur une grille cartésienne
   régulière m x m de l'équation de Poisson à deux dimensions

            d    d        d    d
         - == ( == u ) - == ( == u )  = 0     sur [0,1] x [0,1]
           dx   dx       dy   dy

  avec les conditions aux limites de Dirichlet

         u = 20     sur (0,y)                 , avec 0 <=  y  <= 1
         du/dn = 1  sur (1,y), (x,0) et (x,1) , avec 0 <= x,y <= 1 .

  La numérotation des inconnues est lexicographique, la direction x étant
  parcourue avant celle de y. La matrice A est retournée dans le format
  CRS qui est défini via trois tableaux : 'ia', 'ja' et 'a'.

  Arguments
  =========
  m  (input)  - nombre de points par direction dans la grille
                (les valeurs m inférieures à 2 ne sont pas valides)
  n  (output) - pointeur vers le nombre d'inconnus dans le système
  ia (output) - pointeur vers le tableau 'ia' de la matrice A
  ja (output) - pointeur vers le tableau 'ja' de la matrice A
  a  (output) - pointeur vers le tableau 'a' de la matrice A
  b  (output) - pointeur vers le tableau 'b'

*/


/*longueur de la pièce*/

  int  L = 5;

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
double Wt= 60; // represente la puissance du radiateur multiplié par la surface de ce dernier !



	//Radiateur 1 coordonées

    int xR1d = df;
    int xR1f = ff;
    int yR1d = dp;
    int yR1f = dp + (m-1)/25 ;

    //Radiateur 2 coordonées

    int xR2d = (m-1)/2;
    int xR2f = xR2d + (m-1)/25;
    int yR2d = (2*(m-1))/5;
    int yR2f = (4*(m-1))/5;

    int  ind, n4,n3,n5,nnz;
    double invh2;

    if(m <= 1) {
        printf("\n ERREUR : m = %d n'est pas une valeur valide\n\n",m);
        return 1;
    }


     invh2 = (m-1)*(m-1)/(L*L);
    *n  = ((m-2)*(yP-1))+ (m-2 -yP+1)*(xP-1);
     n3 = 5;
     n4= (m-2) +(m-2-1) + (xP -1) + (m-2-yP + 1 -1) + (m-2 - xP) +(yP - 1 - 2) - 5 ;
     n5 = *n - n3 - n4;
     nnz = 5*n5 + 3*n3 + 4*n4;
     int nal = 3*(*n) -2*m + 4  ;
     int nau = 3*(*n) - 2*m +4  ;
     double W = Wt/((yR1f-yR1d)*h +1)*((xR1f - xR1d)*h +1); // PUISSANCE PAR POINT DE LA GRILLE APPARTENANT AU RADIATEUR

    /* allocation des tableaux */

    *ia  = malloc((*n + 1) * sizeof(int));
    *ja  = malloc(nnz * sizeof(int));
    *a   = malloc(nnz * sizeof(double));
    *b   = malloc(*n * sizeof(double));

    // allocution matrice L
    *ial = malloc((*n+1)*sizeof(int));
    *jal = malloc(nal*sizeof(int));
    *al = malloc(nal*sizeof(double));
    // allocution matrice U
    *iau = malloc((*n+1)*sizeof(int));
    *jau = malloc(nau*sizeof(int));
    *au = malloc(nau*sizeof(double));


    /* allocation réussite? */

    if (*ia == NULL || *ja == NULL || *a == NULL || *b == NULL ) {
        printf("\n ERREUR : pas assez de mémoire pour générer le système\n\n");
        return 1;
    }

  

    ind = 0;
    nnz = 0;

    int nnzl = 0;
    int nnzu = 0;

	for (int iy = 1; iy < yP ;iy++){ // on s'arrete à  Y = 2 compris

        for( int ix = 1; ix < m-1; ix++){




            ind = (ix-1) + (iy -1)*(m-2);

            (*ia)[ind] = nnz;
            (*ial)[ind] = nnzl;
            (*iau)[ind] = nnzu;
            (*b)[ind] = rho(ix,iy,xR1d,xR1f,yR1d,yR1f,xR2d,xR2f,yR2d,yR2f,W);




            //remplissage voisin-sud

		          if(iy >1) {

		                (*a)[nnz] = -invh2;
                    (*al)[nnzl] = -invh2;
                    (*ja)[nnz] = ind - (m-2) ;
                    (*jal)[nnzl] = ind - (m-2);
		                nnz++;
                    nnzl++;


        }




            // Voisin-Ouest

            if(ix==1){

                if(iy <= fp && iy >= dp){

                    (*b)[ind ] = (*b)[ind] + Tp*invh2;

                 }
            }

            else{

                (*a)[nnz] = -invh2;
                (*al)[nnzl] = -invh2;
				        (*ja)[nnz] = ind -1;
                (*jal)[nnzl] = ind - 1;
				        nnz++;
                nnzl++;
            }




            // Remplissage Element Diagonal

            (*a)[nnz] = 4.0*invh2;
            (*ja)[nnz] = ind;
            nnz++;
            (*al)[nnzl] = 4.0*invh2;
            (*jal)[nnzl] = ind;
            nnzl++;
            (*au)[nnzu] = 4.0*invh2;
            (*jau)[nnzu] = ind;
            nnzu++;


            // Remplissage Voisin- Est

            if(ix < m-2){

                (*a)[nnz] = -invh2;
				        (*ja)[nnz] = ind +1;
				        nnz++;
                (*au)[nnzu] = -invh2;
                (*jau)[nnzu] = ind +1;
                nnzu++;

            }

            // Remplissafe Voisin-Nord

            if(iy==yP-1){

                if(ix < xP){

                (*a)[nnz] = -invh2;
    		        (*ja)[nnz] = ind + (m-2) ;
			          nnz++;
                (*au)[nnzu] = -invh2;
    		        (*jau)[nnzu] = ind + (m-2) ;
			          nnzu++;

                }
            }

            else{
                    (*a)[nnz] = -invh2;
    		            (*ja)[nnz] = ind + (m-2) ;
			              nnz++;
                    (*au)[nnzu] = -invh2;
                    (*jau)[nnzu] = ind + (m-2) ;
                    nnzu++;
            }




        }
      }








        for(int iy = yP; iy < m-1 ; iy ++){

            for(int ix = 1; ix < xP; ix ++){


            ind = (yP -1)*(m-2) + (ix-1) + (iy-yP)*(xP -1);

            (*ia)[ind] = nnz;
            (*ial)[ind] = nnzl;
            (*iau)[ind] =nnzu;
            (*b)[ind] = rho(ix,iy,xR1d,xR1f,yR1d,yR1f,xR2d,xR2f,yR2d,yR2f,W);




			         if(iy==yP) {
			                (*a)[nnz] = -invh2;
    		              (*ja)[nnz] = ind - (m-2) ;
                      (*al)[nnzl] = -invh2;
      		            (*jal)[nnzl] = ind - (m-2) ;
			                nnz++;
                      nnzl++;
                    }

            else{
                    (*a)[nnz] = -invh2;
    		    (*ja)[nnz] = ind - (xP - 1) ;
                    (*al)[nnzl] = -invh2;
                    (*jal)[nnzl] = ind - (xP - 1) ;
                    nnz++;
                    nnzl++;
            }

            //  remplissage Voisin-Ouest

            if(ix > 1){

                        (*a)[nnz] = -invh2;
				                (*ja)[nnz] = ind -1;
				                nnz++;
                        (*al)[nnzl] = -invh2;
                        (*jal)[nnzl] = ind -1;
                        nnzl++;
            }



            // Remplissage Element Diagonal

            (*a)[nnz] = 4.0*invh2;
            (*ja)[nnz] = ind;
            nnz++;
            (*al)[nnzl] = 4.0*invh2;
            (*jal)[nnzl] = ind;
            nnzl++;
            (*au)[nnzu] = 4.0*invh2;
            (*jau)[nnzu] = ind;
            nnzu++;


            // Remplissage Voisin-EST

            if(ix < xP - 1){
                          (*a)[nnz] = -invh2;
				                  (*ja)[nnz] = ind +1;
				                  nnz++;
                          (*au)[nnzu] = -invh2;
                          (*jau)[nnzu] = ind +1;
                          nnzu++;

            }

            // Remplissage Voisin-Nord
            if(iy < m-2){

                (*a)[nnz] = -invh2;
    		        (*ja)[nnz] = ind + (xP - 1) ;
			          nnz++;
                (*au)[nnzu] = -invh2;
                (*jau)[nnzu] = ind + (xP - 1) ;
                nnzu++;

            }

    }} // FIN ZONE 2


    // fin discretisation et découpage


    /* dernier élément du tableau 'ia' */
    (*ia)[ind + 1] = nnz;
    (*ial)[ind +1] = nnzl;
    (*iau)[ind +1] = nnzu;
    *nnz_tr = nnzu;
    /* retour habituel de fonction */





    return 0;
}
