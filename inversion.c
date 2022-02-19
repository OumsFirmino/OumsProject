#include <stdio.h>
#include <stdlib.h>
#include <float.h>



int inversion( double **a, int **ja, int **ia,double **inva,int n, int nnz){



(*inva) = malloc(nnz*sizeof(double));



if((*ia)[1]==1){



 int line = 0;





 while(line < n){


 for(int j = (*ia)[line]; j< (*ia)[line +1];j++){

 	if(j==(*ia)[line + 1] - 1){

   	(*inva)[j] = 1/(*a)[j];


  	}


 // ce n'est pas un élement de la diagonale
	 else{


 		 int c = (*ja)[j];
     double den =(*a)[(*ia)[line + 1] - 1];
 		 (*inva)[j] = 0;

 		 for(int k = (*ia)[line] +c ; k < (*ia)[line +1] -1; k++){
			 

  		(*inva)[j] -= (*a)[k]*(*inva)[*ia[k - (*ia)[line]]+c]/den;


 		 }

 		 }






 }

 line++;
 }


 }

 // Triangulaire supérieure

 else{




 int line = n-1;

 while(line >=0){



 for(int i = (*ia)[line +1] -1; i >= (*ia)[line];i--){




 if(i == (*ia)[line]){

  (*inva)[i] = 1/(*a)[i];


 }

 else{
	
 	(*inva)[i] = 0;
 	for(int j = i; j >= (*ia)[line] +1 ;j--){



	(*inva)[i] -=(*a)[j]*(*inva)[(*ia)[(*ja)[j]] + i -j]/(*a)[(*ia)[line]];


 	}



 }


 }
  line--;





 }




 }


 return 0;


 }
