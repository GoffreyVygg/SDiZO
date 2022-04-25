#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <sys/time.h>
#include "dijkstraMacierz.h"

void main() {
	// Wczytywanie liczb
	if((plikWejsciowy = fopen(macierzWej,"r")) == NULL) {
		printf("Blad odczytu\n");
		exit(1);
	}
	int wczytanaLiczba;
	for(int i = 0; i < calkIloscV; i++) {
		for(int j = 0; j < calkIloscV; j++) {
			fscanf(plikWejsciowy, "%d,", &wczytanaLiczba);
			G[i][j] = wczytanaLiczba;
		}
	}
	fclose(plikWejsciowy);
	for(int i = 0; i < V; i++) {
		for(int j = 0; j < V; j++) {
			G2[i][j] = G[i][j];
		}
	}	
	// Petla okreslajaca ilosc iteracji
	for(int i = 0; i < iteracje; i++) {
		// Poczatek pomiaru czasu
		gettimeofday(&start,0);
		// Wyznaczanie SPT
		dijkstra(G2, 0, pomiary);
		// Koniec pomiaru czasu
		gettimeofday(&koniec,0);
		// Obliczenie czasu trwania iteracji
		long sec = koniec.tv_sec - start.tv_sec;
		long usec = koniec.tv_usec - start.tv_usec;
		double czasWykonania = sec + usec*1e-6;
		czasCalkowity += czasWykonania;
		printf("Czas wykonania: %.6f s\n", czasWykonania);
	}	
	// Zapis czasu
	sredniCzas = czasCalkowity/iteracje;
	printf("Sredni czas: %.6f s\n", sredniCzas);
	plikWyjsciowy = fopen(czasDijkstra,"a");
	fprintf(plikWyjsciowy, "%d\t%f\n",V, sredniCzas);
	fclose(plikWyjsciowy);
	printf("\nWcisnij ENTER aby zakonczyc\n", sredniCzas);
	int ch = getchar();
}