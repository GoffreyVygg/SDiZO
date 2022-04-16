#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Zamiana wartosci dwoch elementow
void swap(int *a, int *b) {
	int temp = *a;
    *a = *b;
    *b = temp;
}
 
// Kopcowanie 
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
		largest = left;
  
    if (right < n && arr[right] > arr[largest])
		largest = right;
  
    if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
    }
}
  
// Sortowanie przez kopcowanie  
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
  
    for (int i = n - 1; i >= 0; i--) {
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
    }
}

void main() {
	
   	FILE *fileToRead, *fileToSave, *timeFile;
	// Tablica wielkosci instancji
	int howMany[] = {10, 50, 100, 500, 100, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 300000, 500000, 700000, 900000, 1000000};
	struct timeval start, end;
	// Ilosc iteracji dla danej wielkosci instancji
	int iterations = 10;
	
	// Utworzenie pliku .xls
	timeFile = fopen("timeHeap.xls","w");
	fprintf(timeFile, "Wielkosc instancji\tCzas\n");
	fclose(timeFile);
	
	int n = sizeof(howMany)/sizeof(howMany[0]);
	
	// Petla definiujaca wielkosci instancji do badan
	for(int count = 0; count < n; count++) {
		int numbers[howMany[count]];
		
		double avg = 0, timeSum = 0;

		for(int x = 0; x < iterations; x++) {
			
			// Wczytywanie liczb
			if((fileToRead = fopen("liczby.txt","r")) == NULL) {
				printf("Error\n");
				exit(1);
			}

			int newNumber;

			for(int i = 0; i < howMany[count]; i++) {
				fscanf(fileToRead, "%d, ", &newNumber);
				numbers[i] = newNumber;
			}

			fclose(fileToRead);	
			
			gettimeofday(&start,0);
			
			// Posortowanie liczb
			heapSort(numbers, howMany[count]);
			
			gettimeofday(&end,0);
			
			// Obliczenie czasu trwania iteracji
			long sec = end.tv_sec - start.tv_sec;
			long usec = end.tv_usec - start.tv_usec;
			double singleTime = sec + usec*1e-6;
			timeSum += singleTime;
			printf("Measured time: %.6f s\n", singleTime);
			
			// Zapis posortowanych liczb do pliku
			fileToSave = fopen("sortedHeap.txt","w");

			for(int i = 0; i < howMany[count]; i++) {
				fprintf(fileToSave, "%d, ", numbers[i]);
			}

			fclose(fileToSave);		
		}
		// Obliczenie wartosci sredniej pomiaru czasu z wykonanych iteracji dla zadanej wielkosci instancji
		avg = timeSum/iterations;	
		timeFile = fopen("timeHeap.xls","a");
		fprintf(timeFile, "%d\t%f\n",howMany[count], avg);
		fclose(timeFile);
	}
	
}
