//  10, 20, 50, 100, 500, 1k, 2k, 5k, 10k, 50k, 100k, 200k i 400k

const int ileSlow = 10;

char plikWej[] = "randomDictionary.txt";
char czas[] = "czasHash.xls";

struct timeval start, koniec;
FILE *plikWejsciowy, *plikWyjsciowy, *plik;

double sredniCzas = 0, czasCalkowity = 0;

int iteracje = ileSlow * 0.2;