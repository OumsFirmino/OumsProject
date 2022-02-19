#include <stdlib.h>
#include <stdio.h>
#include "inversion.h"
#include "smoothing.h"
#include "Rinjection.h"
#include "prob.h"
#include "rho.h"
#include "residu.h"
#include "productMV.h"
#include "umfpk.h"
#include "prolongation.h"
#include "add.h"
#include "norme.h"
#include "RFW.h"
#include "transposemultiplication.h"
#include "productMV.h"
#include "printvec.h"
double (*func)(int, int , int , int,int,int,int,int,int,int,double);

void Vcycle(double **xo,double **b,double **a, int **ja, int **ia, double **au, int **jau, int **iau, double **al,int **jal,int **ial,int m, int n,int nnz_tr, int LEVEL , int *count,int itt,FILE *file,double tau){

    func = &rho;
    double *r ;
    r = malloc(n*sizeof(double));
    residu(b,a,ja,ia,xo,&r,n);
    double res1 = norme(&r,n)/norme(b,n);


    // Inversion de L ET U pour smoothing

    double *inval,*invau;
    inversion(al,jal,ial,&inval,n,nnz_tr);
    inversion(au,jau,iau,&invau,n,nnz_tr);

    // Pre-smoothing
    smoothing(b,xo,a,ja,ia,&inval,jal,ial,n,tau);

    residu(b,a,ja,ia,xo,&r,n);
    
    double res2 = norme(&r,n)/norme(b,n);
    

    // Restriction du résidu



                                double *ap,*rc,*ar;
                                int *jr, *ir;
                                int *jp, *ip;
                                int nc;
                                prolongation(m,n,&nc,&ap,&jp,&ip);
                                RFW(&ar,&jr,&ir,m,&nc);
                                //Rinjection(&ar,&jr,&ir,m,&nc);
                                rc = malloc(nc*sizeof(double));
                              //transposemultiplication(&ap,&jp,&ip,&r,&rc,n);
                                productMV(&ar,&jr,&ir,&r,&rc,nc);





    // Matrices de coarse-grid;

                                double *ac,*bc,*auc,*alc;
                                int *iac,*jac,*iauc,*jauc,*ialc,*jalc,nnz_trc;
                                int mc = (m-1)/2 +1;

                                        // Etablissement probleme coarse
                                    prob(mc,&nc,&iac,&jac,&ac,&bc,&alc,&jalc,&ialc,&auc,&jauc,&iauc,func,&nnz_trc);

                                
                                    // Initialization sol de départ
                                    double *uoc;
                                    uoc = malloc(nc*sizeof(double));
                                    for(int i = 0; i < nc;i++){
                                        uoc[i] = 0.0;
                                    }
                                    if(*count +1 < LEVEL){
                                        int count2;
                                        count2 = *count +1;
                                        
                                        Vcycle(&uoc,&rc,&ac,&jac,&iac,&auc,&jauc,&iauc,&alc,&jalc,&ialc,mc,nc,nnz_tr,LEVEL,&count2,itt,file,tau);

                                    }

                                    else{

                                             
                                             solve_umfpack(nc,iac,jac,ac,rc,uoc);
                                    }

    
      
    

                                     // Prolonger l'erreur 
                                    double *ep;
    
   
                                     ep = malloc(n*sizeof(double));
                                     for(int i = 0; i < n; i++){
                                            ep[i] = 0.0;
                                    }
 
                                     productMV(&ap,&jp,&ip,&uoc,&ep,n);
                                     //transposemultiplication(&ar,&jr,&ir,&ec,&ep,&nc);
    

                                    // Ajouter l'erreur à la solution smoothed

                                        add(xo,&ep,xo,n,1);
                                        residu(b,a,ja,ia,xo,&r,n);
                                        double res3 = norme(&r,n)/norme(b,n);
                                        

                                    // post-smoothing

                                    smoothing(b,xo,a,ja,ia,&invau,jau,iau,n,tau);
                                    residu(b,a,ja,ia,xo,&r,n);
                                    double res4 = norme(&r,n)/norme(b,n);
                                    
                                    
                                    if(*count==0){
                                    fprintf(file,"%d %e  %e %e %e \n",itt,res1,res2,res3,res4);
                                    }


    
                         







free(ar);free(jr);free(ir);
 free(inval);free(invau); free(ap);free(jp);free(ip);free(rc);free(ac);free(bc);free(auc);free(alc);free(iac);free(jac);free(iauc);free(jauc);free(ialc);free(jalc);free(r);free(uoc);free(ep);

}