#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <sys/time.h>
#include "bellmanford.h"

int main() {	
	// Wczytywanie liczb
	plikWejsciowy = fopen(macierzWej,"r");
	if(plikWejsciowy == NULL) {
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
	// Petla okreslajaca ilosc iteracji
	for(int i = 0; i < iteracje; i++) {		
		// Utworzenie grafu	
		struct Graph* graph = createGraph(V, E);
		int nrKrawedzi = 0;
		for(int m = 0; m < V; m++) {
			for(int n = 0; n < V; n++) {
				if(m != n) {
					graph->edge[nrKrawedzi].src = m;
					graph->edge[nrKrawedzi].dest = n;
					graph->edge[nrKrawedzi].weight = G[m][n];
					nrKrawedzi++;
				}
			}
		}
		// Poczatek pomiaru czasu
		gettimeofday(&start,0);
		// Wyznaczanie SPT
		BellmanFord(graph, 0, pomiary);		
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
	plikWyjsciowy = fopen(czas,"a");
	fprintf(plikWyjsciowy, "%d\t%f\n",V, sredniCzas);
	fclose(plikWyjsciowy);
	printf("\nWcisnij ENTER aby zakonczyc\n", sredniCzas);
	int ch = getchar();
	return 0;
}