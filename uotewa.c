#include <stdio.h>
#include <stdlib.h>

void main() {
	
	int array[] = {1,2,-5,17,-200,-600};
	int n = sizeof(array)/sizeof(array[0]);
	
	int arrPlus[n];
	int p = 0;
	int arrMinus[n];
	int m = 0;
	
	for(int i = 0; i < n; i++) {
		if(array[i] >= 0) {
			arrPlus[p] = array[i];
			p++;
		}
		else {
			arrMinus[m] = abs(array[i]);
			m++;
		}
	}
	
	for(int i = 0; i < sizeof(arrPlus)/sizeof(arrPlus[0]); i++) {
		printf("%d\n",arrPlus[i]);
	}
	
	for(int i = 0; i < sizeof(arrMinus)/sizeof(arrMinus[0]); i++) {
		printf("%d\n",arrMinus[i]);
	}
	
}