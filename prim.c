#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <sys/time.h>
#include "ini.h"

#define INF 9999999

int G[V][V];

int suma = 0;

// Funkcja wczytujaca macierz kwadratowa z pliku
void WczytajZPliku() {
	FILE *plikWejsciowy;
	// Wybor macierzy
	/*
	const char* macierz = "macierz";
    //int n1 = 1234;
    char *num;
    char buffer[100];
    if (asprintf(&num, "%d", V) == -1) {
        perror("asprintf");
    } else {
        strcat(strcpy(buffer, "macierz"), num);
        strcat(buffer, ".txt");
    }
	*/
	if((plikWejsciowy = fopen("macierz1000.txt","r")) == NULL) {
		printf("Blad odczytu\n");
		exit(1);
	}
	int wczytanaLiczba;
	for(int i = 0; i < V; i++) {
		for(int j = 0; j < V; j++) {
			fscanf(plikWejsciowy, "%d,", &wczytanaLiczba);
			G[i][j] = wczytanaLiczba;
		}
	}
	fclose(plikWejsciowy);	
}

// Do wyznaczania czasu
struct timeval start, koniec;
double sredniCzas = 0, czasCalkowity = 0;

void zmierzCzas() {
	long sec = koniec.tv_sec - start.tv_sec;
	long usec = koniec.tv_usec - start.tv_usec;
	double czasWykonania = sec + usec*1e-6;
	czasCalkowity += czasWykonania;
	printf("Czas wykonania: %.6f s\n", czasWykonania);
}

FILE *plikWyjsciowy;

void main() {
	// Wczytywanie liczb
	WczytajZPliku();
	//plikWyjsciowy = fopen("Prim.xls","a");
	//fprintf(plikWyjsciowy, "Ilosc wierzcholkow\tSredni czas\n");
	//fclose(plikWyjsciowy);
	for(int i = 0; i < iteracje; i++) {
		// Calkowity koszt przejscia
		int sumaWag = 0;
		
		// Program mierzy ilosc wybranych krawedzi, gdyz dla V wierzcholkow, nie bedzie ich wiecej niz V - 1
		int ileKrawedzi = 0;

		// Tablica wskazujaca odwiedzone wierzcholki
		int odwiedzone[V];
		memset(odwiedzone, false, sizeof(odwiedzone));
		odwiedzone[0] = true;	

		// Poczatek pomiaru czasu
		gettimeofday(&start,0);
		
		while(ileKrawedzi < V - 1) {
			int min = INF;
			int x = 0;
			int y = 0;
			for(int i = 0; i < V; i++) {
				if (odwiedzone[i]) {
					for (int j = 0; j < V; j++) {
						if (!odwiedzone[j] && G[i][j]) { 
							if (min > G[i][j]) {
								min = G[i][j];
								x = i;
								y = j;
							}
						}
					}
				}
			}
			printf("Krawedz: %d - %d, Waga: %d\n", x, y, G[x][y]);
			sumaWag += G[x][y];
			odwiedzone[y] = true;
			ileKrawedzi++;
		}
		// Koniec pomiaru czasu
		gettimeofday(&koniec,0);
		
		printf("Calkowity koszt przejscia: %d\n",sumaWag);
		
		// Obliczenie czasu trwania iteracji
		zmierzCzas();
		suma = sumaWag;
	}	
	sredniCzas = czasCalkowity/iteracje;
	printf("Sredni czas: %.6f s\n", sredniCzas);
	plikWyjsciowy = fopen("Prim.xls","a");
	fprintf(plikWyjsciowy, "%d\t%f\t%d\n",V, sredniCzas,suma);
	fclose(plikWyjsciowy);
}