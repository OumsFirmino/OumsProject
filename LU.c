#include <stdio.h>
#include <stdlib.h>
void  LU(double **a, int **ja, int **ia, double **au, int **jau,int **iau,double **al,int **jal, int **ial,int m,int n,int *nnz_tr){

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
  /*coordonnées du point de coupure */
  int xP = (3*(m-1))/L;
  int yP = (2*(m-1))/L ;

double invh2;
invh2 = (m-1)*(m-1)/(L*L);
int nal = 3*(n) -2*m + 4  ;
int nau = 3*(n) - 2*m +4  ;


    /* allocation des tableaux */



    // allocution matrice L
    *ial = malloc((n+1)*sizeof(int));
    *jal = malloc(nal*sizeof(int));
    *al = malloc(nal*sizeof(double));
    // allocution matrice U
    *iau = malloc((n+1)*sizeof(int));
    *jau = malloc(nau*sizeof(int));
    *au = malloc(nau*sizeof(double));

  
    int ind = 0;
    int nnzl = 0;
    int nnzu = 0;

	for (int iy = 1; iy < yP ;iy++){ // on s'arrete à  Y = 2 compris

        for( int ix = 1; ix < m-1; ix++){




            ind = (ix-1) + (iy -1)*(m-2);

            
            (*ial)[ind] = nnzl;
            (*iau)[ind] = nnzu;
              
            




            //remplissage voisin-sud

		          if(iy >1) {

		            
                    (*al)[nnzl] = -invh2;
                    (*jal)[nnzl] = ind - (m-2);
                    nnzl++;
                      }




            // Voisin-Ouest

           if(ix == 1){

           }

            else{

                (*al)[nnzl] = -invh2;       
                (*jal)[nnzl] = ind - 1;
				        nnzl++;
            }




            // Remplissage Element Diagonal
            (*al)[nnzl] = 4.0*invh2;
            (*jal)[nnzl] = ind;
            nnzl++;
            (*au)[nnzu] = 4.0*invh2;
            (*jau)[nnzu] = ind;
            nnzu++;


            // Remplissage Voisin- Est

            if(ix < m-2){
                (*au)[nnzu] = -invh2;
                (*jau)[nnzu] = ind +1;
                nnzu++;

            }

            // Remplissafe Voisin-Nord

            if(iy==yP-1){

                if(ix < xP){

                (*au)[nnzu] = -invh2;
    		    (*jau)[nnzu] = ind + (m-2) ;
			    nnzu++;

                }
            }

            else{
                    (*au)[nnzu] = -invh2;
                    (*jau)[nnzu] = ind + (m-2) ;
                    nnzu++;
            }




        }
      }








        for(int iy = yP; iy < m-1 ; iy ++){

            for(int ix = 1; ix < xP; ix ++){


            ind = (yP -1)*(m-2) + (ix-1) + (iy-yP)*(xP -1);

            (*ial)[ind] = nnzl;
            (*iau)[ind] =nnzu;  
            



			         if(iy==yP) {
			                
                    (*al)[nnzl] = -invh2;
      		        (*jal)[nnzl] = ind - (m-2) ;
                     nnzl++;
                    }

            else{
                   
                    (*al)[nnzl] = -invh2;
                    (*jal)[nnzl] = ind - (xP - 1) ;
                    nnzl++;
            }

            //  remplissage Voisin-Ouest

            if(ix > 1){

                        (*al)[nnzl] = -invh2;
                        (*jal)[nnzl] = ind -1;
                        nnzl++;
            }



            // Remplissage Element Diagonal

            (*al)[nnzl] = 4.0*invh2;
            (*jal)[nnzl] = ind;
            nnzl++;
            (*au)[nnzu] = 4.0*invh2;
            (*jau)[nnzu] = ind;
            nnzu++;


            // Remplissage Voisin-EST

            if(ix < xP - 1){
                    
                          (*au)[nnzu] = -invh2;
                          (*jau)[nnzu] = ind +1;
                          nnzu++;

            }

            // Remplissage Voisin-Nord
            if(iy < m-2){

                (*au)[nnzu] = -invh2;
                (*jau)[nnzu] = ind + (xP - 1) ;
                nnzu++;

            }

    }} // FIN ZONE 2


    // fin discretisation et découpage


    /* dernier élément du tableau 'ia' */
    (*ial)[ind +1] = nnzl;
    (*iau)[ind +1] = nnzu;
    *nnz_tr = nnzu;
    /* retour habituel de fonction */










}