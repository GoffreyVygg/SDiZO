#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void insertionSort(int array[], int n) 
{ 
    int i, element, j; 
    for (i = 1; i < n; i++) { 
		element = array[i]; j = i - 1;  
		while (j >= 0 && array[j] > element) { 
            array[j + 1] = array[j]; 
            j = j - 1; 
        } 
        array[j + 1] = element; 
    } 
}

void main() {
	
   	FILE *fileToRead, *fileToSave, *timeFile;
	int howMany[] = {10, 50, 100, 500, 100, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 300000, 500000, 700000, 900000, 1000000};
	struct timeval start, end;
	int iterations = 10;
	
	timeFile = fopen("timeInsert.xls","w");
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
	
	gettimeofday(&start,0);
	// Sorting
	
	insertionSort(numbers, howMany[count]);
	
	gettimeofday(&end,0);
	long sec = end.tv_sec - start.tv_sec;
	long usec = end.tv_usec - start.tv_usec;
	double singleTime = sec + usec*1e-6;
	timeSum += singleTime;
	printf("Measured time: %.6f s\n", singleTime);
	
	// Saving
	fileToSave = fopen("sortedInsert.txt","w");

	for(int i = 0; i < howMany[count]; i++) {
		fprintf(fileToSave, "%d, ", numbers[i]);
	}

	fclose(fileToSave);		
	}
	avg = timeSum/iterations;	
	timeFile = fopen("timeInsert.xls","a");
	fprintf(timeFile, "%d\t%f\n",howMany[count], avg);
	fclose(timeFile);
	}
}
