#include <iostream>
#include <string>
#include <fstream>
#include <sys/time.h>
#include "hash.h"
using namespace std;
 
// Funkcja haszująca
//------------------
int hf(string s) {
	unsigned int h;
	for(int i = 0; i < s.length(); i++) {
		h = 2 * h + 1 - (s[i] & 1);
	}
	return h % 10;
}
 
int main() {
	string T[ileSlow];
	
	string Array[ileSlow];

    ifstream myFile(plikWej);

    if(!myFile ) {
        printf("Error reading file\n");
        exit(1);
    }
    for(int i = 0; i < ileSlow; i++) {
		myFile >> Array[i];
    }
	
	
	// Zerujemy tablicę haszowaną
	for(int i = 0; i < ileSlow; i++) {
		T [i] = "";
	}
	
	// Tablicę wypełniamy łańcuchami
	gettimeofday(&start,0);
	for(int i = 0; i < ileSlow; i++) {
		// Łańcuch umieszczamy w tablicy haszowanej
		int h = hf (Array[i]);
		int j = h;
		while(true) {
			if(T[j] == "") {
				T[j] = Array[i];
				break;
			}
			if(T[j] == Array[i]) {
				break;
			}
			j = (j + 1) % ileSlow;
			if(j == h) {
				break;
			}
		}
	}
	gettimeofday(&koniec,0);
	long sec = koniec.tv_sec - start.tv_sec;
	long usec = koniec.tv_usec - start.tv_usec;
	double czasWykonania = sec + usec*1e-6;

	// Wyświetlamy zawartość tablicy wraz z wartością funkcji haszującej
	for(int i = 0; i < ileSlow; i++) {
		cout << "T[" << i << "]" << '\t' << "=" << '\t';
		if(T[i] != "" ) {
			cout << T[i] << '\t' << '\t' << "hf( ) = " << hf(T[i]); 
		} else {
			cout << "-";
		}
		cout << endl;
	}
	
	// Sprawdzamy obecność łańcuchów w tablicy haszowanej
	for(int i = 0; i < ileSlow; i += 5) {
		gettimeofday(&start,0);
		int h = hf (Array[i]);  // Hasz łańcucha
		int c = 0;      // Licznik obiegów
		int j = h;
		int p = -1;
		while(true) {
			if(T[j] == "") {
				break;
			}
			if(T[j] == Array[i]) {
				p = j;
				break;
			}
			j = (j + 1) % ileSlow;
			if(j == h) {
				break;
			}
			c++;
			gettimeofday(&koniec,0);
			long secs = koniec.tv_sec - start.tv_sec;
			long usecs = koniec.tv_usec - start.tv_usec;
			double czasUsuwania = secs + usecs*1e-6;
			czasCalkowity += czasUsuwania;
		}
		// Wyświetlamy wyniki
		cout << Array[i] << '\t' << "hf( ) = " << h << '\t' << "c = " << c << " ";
		if( p > -1 ) {
			cout << '\t' << "is in T["<< p << "]";
		} else {
			cout << '\t' << "-";
		}
		cout << endl;
	}
	sredniCzas = czasCalkowity/iteracje;
	plikWyjsciowy = fopen(czas,"a");
	fprintf(plikWyjsciowy, "%d\t%f\t%f\n", ileSlow, czasWykonania, sredniCzas);
	fclose(plikWyjsciowy);
	printf("\nWcisnij ENTER aby zakonczyc\n", sredniCzas);
	int ch = getchar();
	return 0;
}