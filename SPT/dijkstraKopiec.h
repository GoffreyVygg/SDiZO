// Ilosc wierzcholkow
const int V = 20;

// Liczba iteracji
int iteracje = 1;

// True wylacza wyswietlanie wynikow (potrzebne do pomiarow)
bool pomiary = false;

// Nazwa pliku zawierajacego macierz wejsciowa
char macierzWej[] = "Adjacency matrixes/macierz1000.txt";

// Calkowita ilosc wierzcholkow w pliku
const int calkIloscV = 1000;

// Nazwa pliku z wynikami pomiaru czasu dla algorytmu Dijkstry
char czasDijkstra[] = "czasDijkstraStos.xls";

////////////////////////////////////////////////////////////////////////////

// Nieskonczonosc
#define INF 9999999

// Graf
int G[calkIloscV][calkIloscV];

// Pliki
FILE *plikWejsciowy, *plikWyjsciowy, *plik;

// Do wyznaczania czasu
struct timeval start, koniec;
double sredniCzas = 0, czasCalkowity = 0;

struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

struct AdjList {
     
   // Pointer to head node of list
   struct AdjListNode *head;
};

struct Graph {
    int V;
    struct AdjList* array;
};
 
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    for (int i = 0; i < V; ++i) {
		graph->array[i].head = NULL;
	}
 
    return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
struct MinHeapNode {
    int  v;
    int dist;
};

struct MinHeap {
    int size;    
    int capacity; 
    int *pos;   
    struct MinHeapNode **array;
};

struct MinHeapNode* newMinHeapNode(int v, int dist) {
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist) {
      smallest = left;
	}
 
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist) {
      smallest = right;
	}
 
    if (smallest != idx) {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return NULL;
	}
    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
    --minHeap->size;
    minHeapify(minHeap, 0);
    return root;
}

void decreaseKey(struct MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool isInMinHeap(struct MinHeap *minHeap, int v) {
   if (minHeap->pos[v] < minHeap->size) {
     return true;
   }
   return false;
}

void printArr(int dist[], int n) {
    printf("Wierzcholek\tOdleglosc\n");
    for (int i = 0; i < n; ++i) {
        printf("%d \t\t %d\n", i, dist[i]);
	}
}

void dijkstra(struct Graph* graph, int src, bool wyswietlanie) {
    int V = graph->V;
    int dist[V];    
    struct MinHeap* minHeap = createMinHeap(V);
    for (int v = 0; v < V; ++v) {
        dist[v] = INF;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;
    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && dist[u] != INF && pCrawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
	if(!wyswietlanie) {
		printArr(dist, V);
	}
}