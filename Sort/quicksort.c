#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int array[], int low, int high) {
  int pivot = array[high];
  int i = (low - 1);
  
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }

  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}


void main() {
	
   	FILE *fileToRead, *fileToSave, *timeFile;
	int howMany[] = {10, 50, 100, 500, 100, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 300000, 500000, 700000, 900000, 1000000};
	struct timeval start, end;
	int iterations = 10;
	
	timeFile = fopen("timeQuick.xls","w");
	fprintf(timeFile, "Wielkość instancji\tCzas\n");
	fclose(timeFile);
	
	for(int count = 0; count < sizeof(howMany)/sizeof(howMany[0]); count++) {
	int numbers[howMany[count]];
	
	double avg = 0, timeSum = 0;

	for(int x = 0; x < iterations; x++) {

	// Reading
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
	
	
	// Sorting
	
	gettimeofday(&start,0);
	quickSort(numbers, 0, howMany[count] - 1);
	gettimeofday(&end,0);
	long sec = end.tv_sec - start.tv_sec;
	long usec = end.tv_usec - start.tv_usec;
	double singleTime = sec + usec*1e-6;
	timeSum += singleTime;
	printf("Measured time: %.6f s\n", singleTime);


	// Saving
	fileToSave = fopen("sortedQuick.txt","w");

	for(int i = 0; i < howMany[count]; i++) {
		fprintf(fileToSave, "%d, ", numbers[i]);
	}

	fclose(fileToSave);

	}
	avg = timeSum/iterations;	
	timeFile = fopen("timeQuick.xls","a");
	fprintf(timeFile, "%d\t%f\n",howMany[count], avg);
	fclose(timeFile);
	}
}
