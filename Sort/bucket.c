#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define NARRAY 7   // Array size
#define NBUCKET 6  // Number of buckets
#define INTERVAL 10  // Each bucket capacity

struct Node {
  int data;
  struct Node *next;
};

void BucketSort(int arr[]);
struct Node *InsertionSort(struct Node *list);
void print(int arr[]);
void printBuckets(struct Node *list);
int getBucketIndex(int value);

// Sorting function
void BucketSort(int arr[]) {
  int i, j;
  struct Node **buckets;

  // Create buckets and allocate memory size
  buckets = (struct Node **)malloc(sizeof(struct Node *) * NBUCKET);

  // Initialize empty buckets
  for (i = 0; i < NBUCKET; ++i) {
    buckets[i] = NULL;
  }

  // Fill the buckets with respective elements
  for (i = 0; i < NARRAY; ++i) {
    struct Node *current;
    int pos = getBucketIndex(arr[i]);
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = arr[i];
    current->next = buckets[pos];
    buckets[pos] = current;
  }

  // Print the buckets along with their elements
  for (i = 0; i < NBUCKET; i++) {
    printf("Bucket[%d]: ", i);
    printBuckets(buckets[i]);
    printf("\n");
  }

  // Sort the elements of each bucket
  for (i = 0; i < NBUCKET; ++i) {
    buckets[i] = InsertionSort(buckets[i]);
  }

  printf("-------------\n");
  printf("Bucktets after sorting\n");
  for (i = 0; i < NBUCKET; i++) {
    printf("Bucket[%d]: ", i);
    printBuckets(buckets[i]);
    printf("\n");
  }

  // Put sorted elements on arr
  for (j = 0, i = 0; i < NBUCKET; ++i) {
    struct Node *node;
    node = buckets[i];
    while (node) {
      arr[j++] = node->data;
      node = node->next;
    }
  }

  return;
}

// Function to sort the elements of each bucket
struct Node *InsertionSort(struct Node *list) {
  struct Node *k, *nodeList;
  if (list == 0 || list->next == 0) {
    return list;
  }

  nodeList = list;
  k = list->next;
  nodeList->next = 0;
  while (k != 0) {
    struct Node *ptr;
    if (nodeList->data > k->data) {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = nodeList;
      nodeList = tmp;
      continue;
    }

    for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
      if (ptr->next->data > k->data)
        break;
    }

    if (ptr->next != 0) {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = ptr->next;
      ptr->next = tmp;
      continue;
    } else {
      ptr->next = k;
      k = k->next;
      ptr->next->next = 0;
      continue;
    }
  }
  return nodeList;
}

int getBucketIndex(int value) {
  return value / INTERVAL;
}

void print(int ar[]) {
  int i;
  for (i = 0; i < NARRAY; ++i) {
    printf("%d ", ar[i]);
  }
  printf("\n");
}

// Print buckets
void printBuckets(struct Node *list) {
  struct Node *cur = list;
  while (cur) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
}

void main() {
	
   	FILE *fileToRead, *fileToSave, *timeFile;
	int howMany[] = {10, 50, 100, 500, 100, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 300000, 500000, 700000, 900000, 1000000};
	struct timeval start, end;
	int iterations = 1;
	
	timeFile = fopen("timeBucket.xls","w");
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
	
	BucketSort(numbers);
	
	gettimeofday(&end,0);
	long sec = end.tv_sec - start.tv_sec;
	long usec = end.tv_usec - start.tv_usec;
	double singleTime = sec + usec*1e-6;
	timeSum += singleTime;
	printf("Measured time: %.6f s\n", singleTime);
	
	// Saving
	fileToSave = fopen("sortedBucket.txt","w");

	for(int i = 0; i < howMany[count]; i++) {
		fprintf(fileToSave, "%d, ", numbers[i]);
	}

	fclose(fileToSave);		
	}
	avg = timeSum/iterations;	
	timeFile = fopen("timeBucket.xls","a");
	fprintf(timeFile, "%d\t%f\n",howMany[count], avg);
	fclose(timeFile);
	}
}
