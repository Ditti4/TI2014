#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define print(__string) for(__i=0; __string[__i] != '\0'; __i++) putchar(__string[__i]);
int __i;

int readfromfile(double *prices) {
	FILE *fp;
	if(!(fp = fopen("preise.txt", "r"))) return 1;
	fread(prices, sizeof(double), 5, fp);
	fclose(fp);
	return 0;
}

int appendtofile(char **products, int amounts[], double prices[]) {
	FILE *fp;
	char tmpbuf[128];
	int i;
	if(!(fp = fopen("umsatz.txt", "a"))) return 1;
	_strdate(tmpbuf);
	fprintf(fp, "Datum: %s\n", tmpbuf);
	for(i=0; i<5; i++)
		fprintf(fp, "%s:\t%d\t%.2lf\n", *(products+i), amounts[i], amounts[i]*prices[i]);
	return 0;
}

int main() {
	double prices[5];
	char *products[5] = {"Cornetto", "Sandwich", "Flupper", "Polareis", "Solaire"};
	int amounts[5] = {0, 0, 0, 0, 0};
	char next;
	int i, chosen, amount;
	if(readfromfile(prices)) {
		print("Hoppla!");
		return 1;
	}
	do {
		print("Sorte auswaehlen:\n");
		for(i=0; i<5; i++)
			printf("(%d) %s\n", i + 1, products[i]);
		fflush(stdin);
		scanf("%d", &chosen);
		print("Anzahl eingeben:\n");
		fflush(stdin);
		scanf("%d", &amount);
		amounts[chosen] = amount;
		print("Weiter? y/n");
		fflush(stdin);
		next = getchar();
	} while(next == 'y' || next == 'j');
	if(appendtofile(products, amounts, prices)) {
		print("Fehler beim Schreiben in die Datei.");
		return 0;
	}
	
	return 0;
}
