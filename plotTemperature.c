#include <stdio.h>
#include <stdio.h>
#include <math.h>

//Permet l'intéraction avec le programme GNUPLOT pour représenter graphiquement la temperature!

void plotTemperature(){

    FILE *fichier = NULL;
    fichier= popen("gnuplot -persistent", "w");

	if(fichier!=NULL){

        fprintf(fichier,"set title ' Valeur de la température en °C'\n");
		fprintf(fichier,"set xlabel 'Largeur de la pièce'\n");
		fprintf(fichier,"set ylabel 'Longuer de la pièce'\n");
		fprintf(fichier,"set size ratio 0.5\n");
		fprintf(fichier,"set grid\n");
		fprintf(fichier,"set tics out\n");
		fprintf(fichier,"set xrange [0:5]\n");
		fprintf(fichier,"set yrange [0:5]\n");
		fprintf(fichier,"set palette model HSV rgbformulae 3,2,2\n");	



		fprintf(fichier,"plot 'file.txt' u 1:2:3 with points ps 0.3 pointtype 5 palette\n");
		fflush(fichier);
		pclose(fichier);}


	else{	
		printf("ERREUR DANS LA FONCTION plotTemperature\n");}
}
