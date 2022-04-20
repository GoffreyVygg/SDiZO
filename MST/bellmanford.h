// Ilosc wierzcholkow
const int V = 10;

// Liczba iteracji
int iteracje = 1;

// True wylacza wyswietlanie wynikow (potrzebne do pomiarow)
bool pomiary = false;

// Nazwa pliku zawierajacego macierz wejsciowa
char macierzWej[] = "Adjacency matrixes/macierz1000.txt";
	
// Calkowita ilosc wierzcholkow w pliku
const int calkIloscV = 1000;

// Nazwa pliku z wynikami pomiaru czasu dla algorytmu Bellmana-Forda
char czas[] = "czasBellmanFord.xls";

///////////////////////////////////////////////////////////////////////////

// Nieskonczonosc
#define INF 9999999

// Do wyznaczania czasu
struct timeval start, koniec;
double sredniCzas = 0, czasCalkowity = 0;
	
// Pliki
FILE *plikWejsciowy, *plikWyjsciowy, *plik;
	
// Graf
int G[calkIloscV][calkIloscV];

// Ilosc krawedzi w grafie
const int E = V * (V - 1);

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

void printArr(int dist[], int n) {
    printf("Wierzcholek\tOdleglosc\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

void BellmanFord(struct Graph* graph, int src, bool wyswietlanie) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];
    for (int i = 0; i < V; i++) {
		dist[i] = INF;
	}
    dist[src] = 0;
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
			}
        }
    }
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle");
            return; 
        }
    }
	if(!wyswietlanie) {
		printArr(dist, V);
	}
    return;
}