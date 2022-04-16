#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Sortowanie przez zliczanie
void countingSort(int array[], int size) {
	int output[size];
	int max = array[0];
  
	for (int i = 1; i < size; i++) {
		if (array[i] > max)
		max = array[i];
	}

	int counts[65000];

	for (int i = 0; i <= max; ++i) {
		counts[i] = 0;
	}

	for (int i = 0; i < size; i++) {
		counts[array[i]]++;
	}

	for (int i = 1; i <= max; i++) {
		counts[i] += counts[i - 1];
	}

	for (int i = size - 1; i >= 0; i--) {
		output[counts[array[i]] - 1] = array[i];
		counts[array[i]]--;
	}

	for (int i = 0; i < size; i++) {
		array[i] = output[i];
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
	timeFile = fopen("timeCount.xls","w");
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
			
			int arrPlus[n], arrMinus[n], p = 0, m = 0;
			
			// Rozdzielenie oraz posortowanie liczb dodatnich (z zerem) oraz ujemnych osobno
			for(int i = 0; i < howMany[count]; i++) {
				if(numbers[i] >= 0) {
					arrPlus[p] = numbers[i];
					p++;
				}
				else {
					arrMinus[m] = abs(numbers[i]);
					m++;
				}
			}
			
			countingSort(arrMinus, m);
			countingSort(arrPlus, p);
			
			// Zlozenie wynikowej tablicy posortowanych liczb
			for(int i = 0; i < howMany[count]; i++) {
				if(i < m) {
					numbers[i] = (-1)*(arrMinus[m-i-1]);
				}
				else {
					numbers[i] = arrPlus[i-m];
				}
			}
			
			gettimeofday(&end,0);
			
			// Obliczenie czasu trwania iteracji
			long sec = end.tv_sec - start.tv_sec;
			long usec = end.tv_usec - start.tv_usec;
			double singleTime = sec + usec*1e-6;
			timeSum += singleTime;
			printf("Measured time: %.6f s\n", singleTime);
			
			// Zapis posortowanych liczb do pliku
			fileToSave = fopen("sortedCount.txt","w");

			for(int i = 0; i < howMany[count]; i++) {
				fprintf(fileToSave, "%d, ", numbers[i]);
			}

			fclose(fileToSave);		
		}
		// Obliczenie wartosci sredniej pomiaru czasu z wykonanych iteracji dla zadanej wielkosci instancji
		avg = timeSum/iterations;	
		timeFile = fopen("timeCount.xls","a");
		fprintf(timeFile, "%d\t%f\n",howMany[count], avg);
		fclose(timeFile);
	}
	
}
