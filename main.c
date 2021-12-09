#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"



int main(int argc, char *argv[]) {
	
	
	/* Kontrola parametrů příkazové řádky */
	/*
	if(argc != 3){
		perror("ERROR: there must be 2 arguments!!!!!........");
		return 1;
	}*/
	
	pgm* obrazek;
	FILE *f, *vystup;
	int x, sirka, vyska, velikost;
	char znak[2];
	
	//f = fopen(argv[1], "r");
	f = fopen("images/w2test.pgm", "r");
	if(!f) {
		perror("ERROR opening input file!!!!!........");
		return 1;
	}
	
	obrazek = (pgm *) malloc (sizeof(pgm));
	znak[0] = fgetc(f);
	znak[1] = fgetc(f);
	if(znak[0] != 'P' && znak[1] != '5'){
		perror("ERROR: Wrong picture format!!!!!........");
		return 1;
	}
	
	fscanf(f, "%d", &obrazek->w);
	fscanf(f, "%d", &obrazek->h);
	fscanf(f, "%d", &obrazek->max);
	
	//konec radku
	x = fgetc(f);
	
	/* sanity check */
	if(obrazek->w < 0 || obrazek->h < 0 || obrazek->max < 0){
		perror("ERROR: Wrong picture parameters!!!!!........");
		return 1;
	}
	
	sirka = obrazek->w;
	vyska = obrazek->h;
	velikost = sirka * vyska;
	
	/* pole hodnot se kterými se bude pracovat */
	obrazek->data = (int*) malloc(sizeof(int) * velikost);
	
	/* finální pole pixelů, které se bude ukládat do výstupního souboru */
	obrazek->hodnoty = (pixel*) malloc(sizeof(pixel) * velikost);
	
	for(int i = 0; i < velikost; i++){
		x = fgetc(f);
		obrazek->data[i] = x;
		
		/*test, zda je obrazek cernobily*/
		if(x != 0 && x != obrazek->max){
			perror("ERROR: Wrong picture format!!!!!........");
			return 1;
		}
	}
	
	/* první průchod algoritmu CCL*/
	pic_color(obrazek);
	
	/* druhý průchod algoritmu CCL*/
	pic_recolor(obrazek);
	
	//vystup = fopen(argv[2], "w");
	vystup = fopen("C:/Users/sabal/C projects/semestralka/vystup.pgm", "w");
	if(!vystup) {
		perror("ERROR opening output file!!!!!........");
		return 1;
	}
	fprintf(vystup, "P5\n");
	fprintf(vystup, "%d %d\n", sirka, vyska);
	fprintf(vystup, "%d\n", obrazek->max);
	
	for(int i = 0; i < velikost; i++){
		fputc(obrazek->hodnoty[i], vystup);
	}
	fprintf(vystup, "\n");
	fclose(vystup);
	
	/* uvolnění paměti */
	tabulka *walk = obrazek->tab_first;
	while(walk != NULL){
		tabulka *tab = walk;
		free(tab->hodnoty);
		free(tab);
		walk = walk->next;
	}
	free(obrazek->data);
	free(obrazek->hodnoty);
	free(obrazek);
	
	return 0;
}