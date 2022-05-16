const int ileSlow = 20;

char plikWej[] = "randomDictionary.txt";
char czas[] = "czasBST.xls";

struct timeval start, koniec;
FILE *plikWejsciowy, *plikWyjsciowy, *plik;

double sredniCzas = 0, czasCalkowity = 0;

int iteracje = ileSlow * 0.2;