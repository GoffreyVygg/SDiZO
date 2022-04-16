#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(){
	
	FILE *plik_odczytu, *plik_zapisu, *plik_wynikowy;
	int liczebnosc_zbioru = 10;
	int tablica_instancji[]={10, 50, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 300000, 500000, 700000, 900000,1000000};
	int rozmiar=16;
	int powtorzenia=100;
	int liczby[10000000];
	int i, j, k, m, x;
	double srednia[rozmiar], suma_czasu=0;
	struct timeval poczatek, koniec;
	
	for(int ktora_instancja=0; ktora_instancja<rozmiar;ktora_instancja++){
		liczebnosc_zbioru=tablica_instancji[ktora_instancja]+1;
		
		for(int liczba_powtorzen=0; liczba_powtorzen<powtorzenia; liczba_powtorzen++){
			if((plik_odczytu = fopen("liczby.txt","r"))==NULL){
				printf("Blad odczytu pliku.\n");
				exit(1);
			}
			int nowa_liczba;
			for(int i=1; i<=liczebnosc_zbioru; i++){
				fscanf(plik_odczytu, "%d, ", &nowa_liczba);
				liczby[i]=nowa_liczba;
			}
			fclose(plik_odczytu);
			gettimeofday(&poczatek, 0);
			
			// sortowanie przez kopcowanie
			int element_wstawiany, pozycja_rodzica, pozycja_dziecka;
			for (i = 2; i <= liczebnosc_zbioru; i++){
				pozycja_dziecka = i; 
				pozycja_rodzica = pozycja_dziecka / 2;
				element_wstawiany = liczby[i];
				while ((pozycja_rodzica > 0) && (liczby[pozycja_rodzica] < element_wstawiany)){
					liczby[pozycja_dziecka] = liczby[pozycja_rodzica];
					pozycja_dziecka = pozycja_rodzica; pozycja_rodzica = pozycja_dziecka / 2;
				}
				liczby[pozycja_dziecka] = element_wstawiany;
			}
			int pozycja_wiekszego_dziecka;
			for (i = liczebnosc_zbioru; i > 1; i--){
				int zmienna=liczby[1];
				liczby[1]=liczby[i];
				liczby[i]=zmienna;
				pozycja_dziecka = 1; pozycja_rodzica = 2;
				while (pozycja_rodzica < i){
					if ((pozycja_rodzica + 1 < i) && (liczby[pozycja_rodzica + 1] > liczby[pozycja_rodzica]))
						pozycja_wiekszego_dziecka = pozycja_rodzica + 1;
					else
						pozycja_wiekszego_dziecka = pozycja_rodzica;
					if (liczby[pozycja_wiekszego_dziecka] <= liczby[pozycja_dziecka]) break;
					int zmienna=liczby[pozycja_dziecka];
					liczby[pozycja_dziecka]=liczby[pozycja_wiekszego_dziecka];
					liczby[pozycja_wiekszego_dziecka]=zmienna;
					pozycja_dziecka = pozycja_wiekszego_dziecka; 
					pozycja_rodzica = pozycja_dziecka + pozycja_dziecka;
				}
			}
			
			//pomiar czasu
			gettimeofday(&koniec, 0);
			long sekundy = koniec.tv_sec - poczatek.tv_sec;
			long mikrosekundy = koniec.tv_usec - poczatek.tv_usec;
			double razem = sekundy + mikrosekundy*1e-6;
			suma_czasu=suma_czasu+razem;
			printf("Zmierzony czas dla instacji %d liczb: %.6f sekund.\n", tablica_instancji[ktora_instancja], razem);
		}
		srednia[ktora_instancja]=suma_czasu/powtorzenia;
		suma_czasu=0;
	}
	// Wyświetlamy wynik sortowania
	/*
	for(int i=1;i<liczebnosc_zbioru;i++){
		printf("%d, ", liczby[i]);
	}
	*/
	//zapisywanie do pliku
	plik_wynikowy = fopen("wynik.txt","w");
	fprintf(plik_wynikowy, "Srednie czasy:\n");
	for(int i=0; i<rozmiar;i++){
		fprintf(plik_wynikowy, "%f\n", srednia[i]);
	}
	fclose(plik_wynikowy);
	
	//zapisywanie posortowanych do pliku
	plik_zapisu = fopen("posortowane.txt","w");
	for(int i=1; i<liczebnosc_zbioru; i++){
		fprintf(plik_zapisu, "%d, ", liczby[i]);
	}
	fclose(plik_zapisu);
	
	
}