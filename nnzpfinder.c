#include <stdlib.h>
#include <stdio.h>



void nnzpfinder(int *nnzp,int m){
int xP = 3*(m-1)/5;
int yP = 2*(m-1)/5;

int nnz = 0;




for (int iy = 1; iy < yP ;iy++){

         
            for( int ix = 1; ix < m-1; ix++){

            
            

            // ix et iy pairs
            if(ix%2==0 && iy%2==0){

               
                
                nnz++;
                  }
            
            // ix pair et iy impair

            if(ix%2==0 && iy%2!=0){

                if(iy ==1){

                    
                    nnz++;
 
                }
                else if(iy== yP-1){
                    if(ix >= xP){

                            
                            nnz++;

                    }
                    else{
                        // SUD
                       
                            nnz++;
                        // NORD
                           
                            nnz++;


                    }

                }
                else{

                    // SUD
                            
                            nnz++;
                        // NORD
                           
                            nnz++;

                }



            }
            // ix impair et iy pair
            if(ix%2!=0 && iy%2==0){

                if(ix==1){ //EST ONLY

                            
                            nnz++;

                }

                else if(ix == (m-2)){    // WEST ONLY

                         
                            nnz++;

                }
                else{

                    // WEST 
                            
                            nnz++;

                    //EST 

                         
                            nnz++;

                }




            }
            if(ix%2!=0 && iy%2!=0){

                if(iy==1){
                    if(ix==1){
                        // COIN S-D
                           
                            nnz++;

                    }
                    else if(ix==m-2){
                            // COIN S-G
                       
                            nnz++;

                    }
                    else{
                         // COIN S-D
                            
                             nnz++;
                        // COIN S-G
                             
                             nnz++;



                    }


                }

                else if(iy==yP -1){

                    if(ix == m-2){ // COIN I_G

                         
                             nnz++;

                    }
                    if(ix > xP && ix < m-2){
                        // COIN I_G

                             
                             nnz++;
                        
                        // COIN I_D

                     
                             nnz++;

                    }
                    if(ix == xP -1){
                         // COIN I_G

                             
                             nnz++;
                        
                        // COIN I_D

                       
                             nnz++;

                         // COIN S_G

                          
                             nnz++;


                    }
                    if(ix==1){

                        // COIN I_D

                           
                             nnz++;
                        // COIN S_D

                           
                             nnz++;


                    }

                    if(ix>1 && ix<xP-1){

                        // COIN I_G

                             
                             nnz++;
                        // COIN I_D

                          
                             nnz++;
                         // COIN S_G

                           
                             nnz++;
                         // COIN S_D

                            
                             nnz++;


                    }


                }
                else{

                    if(ix==1){
                            // COIN I_D

                         
                             nnz++;

                            // COIN S_D

                         
                             nnz++;

                    }

                    else if(ix ==m-2){

                        // COIN I_G

                             
                             nnz++;
                        // COIN S_G

                          
                             nnz++;

                    }

                    else{

                         // COIN I_G

                           
                             nnz++;
                        // COIN I_D

                           
                             nnz++;
                         // COIN S_G

                         
                             nnz++;
                         // COIN S_D

                             
                             nnz++;


                    }


                }


            }
           






              
              }





}

// ZONE 2

for(int iy = yP; iy < m-1; iy++){

    for(int ix = 1; ix < xP; ix++){

        
        
        if(ix%2==0 && iy%2==0){

               
                nnz++;
                  }
        if(ix%2==0 && iy%2!=0){

            if(iy==m-2){
          
                nnz++;
            }
            else{
          
                nnz++;
           
                nnz++;

            }
        }
        if(ix%2!=0 && iy%2==0){
            if(ix==1){

              
                nnz++;


            }
            else if(ix == xP-1){
             
                nnz++;

            }
            else{

       
                nnz++;
            
                nnz++;


            }

        }
    if(ix%2!=0 && iy%2!=0){

        if(ix==1){

            if(iy == m-2){

                
                nnz++;

            }
            else{
              
                nnz++;
             
                nnz++;


            }

        }
        else if(ix == xP -1){
                if(iy == m-2){

                   
                    nnz++;

                }
                else{
               
                nnz++;
               
                nnz++;


            }



        }
        else{

            if(iy==m-2){
              
                nnz++;
                
                nnz++;


            }
            else{
             
                nnz++;
          
                nnz++;

                
                nnz++;
               
                
                nnz++;


            }


        }



    }


   
    }

}

*nnzp = nnz;

}