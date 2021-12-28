#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

/**
* funkce načte data ze vstupního souboru, uloží je do struktury 'pgm' a jako návratovou hodnotu vrátí ukazatel na tuto strukturu
*/
int loadData(char *soubor, pgm *obrazek){
	
	/* deklarace potřebných proměnných*/
	FILE *f;
	int x, velikost, velikost_nazvu, i;
	char znak[2];
	
	velikost_nazvu = strlen(soubor);
	
	/* sanity check */
	if(soubor == NULL || obrazek == NULL){
		return EXIT_FAILURE;
	}
		
	/* kontrola, zda je vstupní soubor zadán správně */
	if((soubor[velikost_nazvu - 1] != 'm') || (soubor[velikost_nazvu - 2] != 'g') || (soubor[velikost_nazvu - 3] != 'p') || (soubor[velikost_nazvu - 4] != '.')){
		strcat(soubor, ".pgm");
	}
	
	f = fopen(soubor, "r"); 
		if(!f) {
			perror("ERROR opening input file!!!!!........");
			return EXIT_FAILURE;
		}
		
	/* první 2 znaky ve vstupním souboru, musí být 'P5' */
	znak[0] = fgetc(f);
	znak[1] = fgetc(f);
	if(znak[0] != 'P' && znak[1] != '5'){
		perror("ERROR: Wrong picture format!!!!!........");
		return EXIT_FAILURE;
	}
	
	/* parametry obrázku */
	fscanf(f, "%d", &obrazek->w);
	fscanf(f, "%d", &obrazek->h);
	fscanf(f, "%d", &obrazek->max);
	
	/* konec radku */
	x = fgetc(f);
	
	/* sanity check */
	if(obrazek->w < 0 || obrazek->h < 0 || obrazek->max < 0){
		perror("ERROR: Wrong picture parameters!!!!!........");
		return EXIT_FAILURE;
	}
	
	velikost = obrazek->w * obrazek->h;
	
	/* pole hodnot se kterými se bude pracovat */
	obrazek->data = (int*) malloc(sizeof(int) * velikost);
	
	/* finální pole pixelů, které se bude ukládat do výstupního souboru */
	obrazek->hodnoty = malloc(sizeof(pixel) * velikost);
	
	/* finální hodnoty se před průchodem CCL algoritmu nastaví na 0 */
	for(i = 0; i < velikost; i++){
		obrazek->hodnoty[i] = 0;
	}
	
	/* dočasné hodnoty se kterými se bude pracovat při průchodu algoritmem */ 
	for(i = 0; i < velikost; i++){
		x = fgetc(f);
		obrazek->data[i] = x;
		
		/* test, zda je obrazek cernobily */
		if(x != 0 && x != obrazek->max){
			perror("ERROR: Wrong picture format!!!!!........, The input picture must contain only white or black pixels");
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

/**
* funkce zapíše data do výstupního souboru tak, aby vzniknul obrázek v pgm formátu
*/
int dataOutput(char *soubor, pgm *obrazek){
	
	int sirka, vyska, velikost, velikost_nazvu, i;
	FILE *vystup;
	
	velikost_nazvu = strlen(soubor);
	
	/* sanity check */
	if(soubor == NULL || obrazek == NULL){
		return EXIT_FAILURE;
	}
	
	/* kontrola, zda je výstupní soubor správného formátu */
	if((soubor[velikost_nazvu - 1] != 'm') || (soubor[velikost_nazvu - 2] != 'g') || (soubor[velikost_nazvu - 3] != 'p') || (soubor[velikost_nazvu - 4] != '.')){
		printf("ERROR: output file must be pgm format");
		return EXIT_FAILURE;
	}
	
	vystup = fopen(soubor, "w"); 
	
	if(!vystup){
		perror("ERROR opening output file!!!!!........");
		return EXIT_FAILURE;	
	}
	
	sirka = obrazek->w;
	vyska = obrazek->h;
	velikost = vyska * sirka;
	
	fprintf(vystup, "P5\n");
	fprintf(vystup, "%d %d\n", sirka, vyska);
	fprintf(vystup, "%d\n", obrazek->max);
	
	for(i = 0; i < velikost; i++){
		fprintf(vystup, "%c", obrazek->hodnoty[i]);
	}
	
	fclose(vystup);
	
	return EXIT_SUCCESS;
}

/**
* funkce která uvolní všechnu dosud neuvolněnou paměť
*/
int freeMemory(pgm *obrazek){
	
	/* proměnná pro průchod spojového seznamu */
	tabulka *walk = obrazek->tab_first;
	
	/* sanity check */
	if(obrazek == NULL){
		return EXIT_FAILURE;
	}
	
	while(walk != NULL){
		tabulka *tab = walk;
		walk = walk->next;
		free(tab->hodnoty);
		free(tab);
	}
	
	free(obrazek->data);
	free(obrazek->hodnoty);
	free(obrazek);
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
	
	pgm* obrazek;
	int delka_nazvu;
	
	/* Kontrola parametrů příkazové řádky */
	if(argc != 3){
		printf("ERROR: there must be 2 arguments!!!!!........");
		return EXIT_FAILURE;
	}
	
	/* názvy souborů z příkazové řádky */
	delka_nazvu = strlen(argv[1]);
	char vstupni_soubor[delka_nazvu];
	delka_nazvu = strlen(argv[2]);
	char vystupni_soubor[delka_nazvu];
	
	/* zpracování vstupních dat */
	obrazek = (pgm *) malloc (sizeof(pgm));
	strcpy(vstupni_soubor, argv[1]);
	if(loadData(vstupni_soubor, obrazek)){
		return EXIT_FAILURE;
	}

	/* první průchod algoritmu CCL*/
	pic_color(obrazek);
	
	/* druhý průchod algoritmu CCL*/
	pic_recolor(obrazek);
	
	/* zápis dat do výstupního souboru */
	strcpy(vystupni_soubor, argv[2]);
	if(dataOutput(vystupni_soubor, obrazek)){
		return EXIT_FAILURE;
	}
	
	/* uvolnění paměti */
	if(freeMemory(obrazek)){
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}