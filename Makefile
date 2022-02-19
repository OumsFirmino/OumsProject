# librairies de SuiteSparse
L1 = SuiteSparse/UMFPACK/Lib/libumfpack.a
L2 = SuiteSparse/CHOLMOD/Lib/libcholmod.a
L3 = SuiteSparse/AMD/Lib/libamd.a
L4 = SuiteSparse/CAMD/Lib/libcamd.a
L5 = SuiteSparse/COLAMD/Lib/libcolamd.a
L6 = SuiteSparse/CCOLAMD/Lib/libccolamd.a
L7 = SuiteSparse/metis-4.0/libmetis.a
L8 = SuiteSparse/SuiteSparse_config/libsuitesparseconfig.a
LIB = $(L1) $(L2) $(L3) $(L4) $(L5) $(L6) $(L7) $(L8) -lm -lblas -llapack

COPT = -O3 -Wall -ggdb


default: main

clean:
	rm *.o
	rm main

main: main.c prob.o  time.o Vcycle.o copie.o productVS.o conjugateGradient.o cGVcycle.o convergenceFactor.o stabilityCheck.o printvec.o normalisation.o transposemultiplication.o inversion.o umfpack.o twogrid.o  temperature.o plotTemperature.o rho.o flux.o residu.o add.o norme.o productMV.o LU.o smoothing.o nnzpfinder.o prolongation.o Rinjection.o RFW.o
	cc $(COPT) $^ -o $@ $(LIB)

umfpack.o: umfpack.c
	cc $(COPT) -c $< -o $@ -ISuiteSparse/UMFPACK/Include \
  -ISuiteSparse/SuiteSparse_config  -ISuiteSparse/AMD/Include

%.o: %.c
	cc $(COPT) -c $< -o $@
