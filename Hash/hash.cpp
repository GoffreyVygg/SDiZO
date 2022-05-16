#include <iostream>
#include <string>
#include <fstream>
#include <sys/time.h>
#include "hash.h"
using namespace std;
 
// Funkcja haszująca
//------------------
int hf (string s) {
  unsigned int h, i;

  h = 0;
  for( i = 0; i < s.length( ); i++ )
    h = 2 * h + 1 - ( s [ i ] & 1 );
  return h % 10;
}

// Funkcja tworzy łańcuch 4 znakowy z A i B
// na podstawie wartości bitów x
//-----------------------------------------
string s4 ( int x )
{
  string s = "";
  int m = 8;  // Maska bitowa
  while( m )
  {
    s += ( x & m )? 'B' : 'A';
    m >>= 1;
  }
  return s;
}
 
int main() {
	string Array[ileSlow];

    ifstream myFile(plikWej);

    if (!myFile ) {
        printf("Error reading file\n");
        exit(1);
    }
    for (int i = 0; i < ileSlow; i++) {
		myFile >> Array[i];
    }
	struct node* root = NULL;
	gettimeofday(&start,0);
    for (int i = 0; i < ileSlow; i++) {
		if (i == 0) {
			root = insert(root, Array[i]);
		} else {
			insert(root, Array[i]);
		}			
    }
	gettimeofday(&koniec,0);
	long sec = koniec.tv_sec - start.tv_sec;
	long usec = koniec.tv_usec - start.tv_usec;
	double czasWykonania = sec + usec*1e-6;
	
	plikWyjsciowy = fopen(czas,"a");
	fprintf(plikWyjsciowy, "%d\t%f\n", ileSlow, czasWykonania);
	fclose(plikWyjsciowy);
	
	inorder(root);

	printf("\nPoczatek pomiaru czasu usuwania:\n");
	for (int i = 0; i < ileSlow; i += 5) {
		gettimeofday(&start,0);
		root = deleteNode(root, Array[i]);	
		gettimeofday(&koniec,0);
		long secs = koniec.tv_sec - start.tv_sec;
		long usecs = koniec.tv_usec - start.tv_usec;
		double czasUsuwania = secs + usecs*1e-6;
		czasCalkowity += czasUsuwania;
		printf("%f\t%f\n", czasCalkowity, czasUsuwania);
	}
	sredniCzas = czasCalkowity/iteracje;
	printf("Sredni czas: %.6f s\n\n", sredniCzas);
    inorder(root);
	printf("\nWcisnij ENTER aby zakonczyc\n", sredniCzas);
	int ch = getchar();
	return 0;
    return 0;
}