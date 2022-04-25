// Ilosc wierzcholkow
#define V 20

// Liczba iteracji
int iteracje = 1;

// True wylacza wyswietlanie wynikow (potrzebne do pomiarow)
bool pomiary = false;

// Nazwa pliku zawierajacego macierz wejsciowa
char macierzWej[] = "Adjacency matrixes/macierz1000.txt";

// Calkowita ilosc wierzcholkow w pliku
#define calkIloscV 1000

// Nazwa pliku z wynikami pomiaru czasu dla algorytmu Dijkstry
char czasDijkstra[] = "czasDijkstra.xls";

////////////////////////////////////////////////////////////////

// Nieskonczonosc
#define INF 9999999

// Graf
int G[calkIloscV][calkIloscV];
int G2[V][V];

// Pliki
FILE *plikWejsciowy, *plikWyjsciowy, *plik;

// Do wyznaczania czasu
struct timeval start, koniec;
double sredniCzas = 0, czasCalkowity = 0;

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
    if (sciezka[j] == -1) {
        return;
	}
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
void dijkstra(int graf[V][V], int zadanyV, bool wyswietlanie)
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
	if(!wyswietlanie) {
		wypiszRozwiazanie(odleglosci, V, tablicaSPT);
		printf("\n");
	}
}