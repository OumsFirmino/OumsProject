#include <stdio.h>
#include <stdlib.h>

void restriction(double **ap,int **jp,int **ip, double **vn,double **vc, int line_number){








int line = 0;

while(line < line_number){



for(int i = (*ip)[line]; i< (*ip)[line +1]; i++){


(*vc)[(*jp)[i]] += ((*ap)[i]*((*vn)[line]));


}

line++;

}




}