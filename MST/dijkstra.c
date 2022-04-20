#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <sys/time.h>
#include "dijkstrac.h"

// Nieskonczonosc
#define INF 9999999

// Graf
int G[1000][1000];
int G2[V][V];

// Pliki
FILE *plikWejsciowy, *plikWyjsciowy, *plik;

// Do wyznaczania czasu
struct timeval start, koniec;
double sredniCzas = 0, czasCalkowity = 0;

// Funkcja wczytujaca macierz kwadratowa z pliku
void WczytajZPliku() {
	// Wybor macierzy
	if((plikWejsciowy = fopen(macierzWej,"r")) == NULL) {
		printf("Blad odczytu\n");
		exit(1);
	}
	int wczytanaLiczba;
	for(int i = 0; i < 1000; i++) {
		for(int j = 0; j < 1000; j++) {
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
}


// Funkcja mierzaca czas
void zmierzCzas() {
	long sec = koniec.tv_sec - start.tv_sec;
	long usec = koniec.tv_usec - start.tv_usec;
	double czasWykonania = sec + usec*1e-6;
	czasCalkowity += czasWykonania;
	printf("Czas wykonania: %.6f s\n", czasWykonania);
}

// Wyznaczenie najkrotszej sciezki
int znajdzNajkrotsza(int odleglosc[], bool sptSet[])
{
    int min = INF;
	int indeks;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && odleglosc[v] <= min) {
            min = odleglosc[v];
			indeks = v;
		}
	}
    return indeks;
}

// Wyswietlanie sciezki 
void wypiszSciezke(int sciezka[], int j)
{
    if (sciezka[j] == -1)
        return;
    wypiszSciezke(sciezka, sciezka[j]);
    printf("%d ", j);
}
 
 
// Wyswietlanie rozwiazania
int wypiszRozwiazanie(int odleglosc[], int n, int parent[])
{
    int src = 0;
    printf("Wierzcholek\t Odleglosc\tSciezka");
    for (int i = 1; i < V; i++) {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, odleglosc[i], src);
        wypiszSciezke(parent, i);
    }
}


// Funkcja realizujaca wyznaczenie SPT 
void dijkstra(int graf[V][V], int zadanyV)
{
    int odleglosci[V];
    bool sptSet[V] = { false };
    int tablicaSPT[V] = { -1 };
    for (int i = 0; i < V; i++) {
        odleglosci[i] = INF;
    }
    odleglosci[zadanyV] = 0;
    for (int nrWierzcholka = 0; nrWierzcholka < V - 1; nrWierzcholka++) {
        int u = znajdzNajkrotsza(odleglosci, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graf[u][v] && odleglosci[u] + graf[u][v] < odleglosci[v]) {
                tablicaSPT[v] = u;
                odleglosci[v] = odleglosci[u] + graf[u][v];
            }
    }
    //wypiszRozwiazanie(odleglosci, V, tablicaSPT);
	printf("\n");
}

void main() {
	// Wczytywanie liczb
	WczytajZPliku();	
	// Petla okreslajaca ilosc iteracji
	for(int i = 0; i < iteracje; i++) {
		// Poczatek pomiaru czasu
		gettimeofday(&start,0);
		// Wyznaczanie SPT
		dijkstra(G2, 0);
		// Koniec pomiaru czasu
		gettimeofday(&koniec,0);
		// Obliczenie czasu trwania iteracji
		zmierzCzas();
	}	
	// Zapis czasu
	sredniCzas = czasCalkowity/iteracje;
	printf("Sredni czas: %.6f s\n", sredniCzas);
	plikWyjsciowy = fopen(czasDijkstra,"a");
	fprintf(plikWyjsciowy, "%d\t%f\n",V, sredniCzas);
	fclose(plikWyjsciowy);
}