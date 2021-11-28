#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"



int main(int argc, char *argv[]) {
	//char* soubor = argv[0];
	pgm* obrazek;
	FILE* f;
	int x;
	char znak[256];
	
	f = fopen("C:/Users/sabal/C projects/semestralka/images/183_3258532_1.pgm", "r");
	if(!f) {
		perror("ERROR opening file!!!!!........");
		return 1;
	}
	
	obrazek = (pgm *) malloc (sizeof(pgm));
	fscanf (f, "%s", znak);
	
	fscanf(f, "%d", &obrazek->w);
	fscanf(f, "%d", &obrazek->h);
	//obrazek->max = fgetc(f);
	fscanf(f, "%d", &obrazek->max);
	printf("WIDTH: %d, HEIGHT %d\n", obrazek->w, obrazek->h);
	printf("MAX: %d\n", obrazek->max);
	x = fgetc(f);
	
	int velikost = obrazek->w * obrazek->h;
	//printf("VELIKOST: %d\n", velikost);
	
	obrazek->data = (int*) malloc(sizeof(int) * velikost);
	obrazek->hodnoty = (pixel*) malloc(sizeof(pixel) * velikost);
	obrazek->tab = (tabulka**) malloc(sizeof(tabulka) * 200000);
	for(int i = 0; i < velikost; i++){
		x = fgetc(f);
		obrazek->data[i] = x;
		//printf("%d: %d\n",i,  obrazek->data[i]);
	}
	
	pic_color(obrazek);
	
	/*
	for(int i = 0; i < 100; i++){	
			printf("%d: %d, %d, %d, %d\n", i, obrazek->tab[i]->hodnoty[0], obrazek->tab[i]->hodnoty[1], obrazek->tab[i]->hodnoty[2], obrazek->tab[i]->hodnoty[3]);
	}*/
	/*
	for(int i = 0; i < obrazek->h * obrazek->w; i++){	
			printf("%d: %d\n", i, obrazek->data[i]);
	}*/
	

	printf("pocetTab: %d\n", obrazek->tab_size);
	for(int i = 0; i < obrazek->tab_size; i++){
		printf("tab: %d, vel: %d\n", i, obrazek->tab[i]->size);
		for (int j = 0; j < obrazek->tab[i]->size; j++){
			printf("hodnota: %d\n", obrazek->tab[i]->hodnoty[j]);
		}
	}
	
	adj_tab(obrazek);
	
	printf("pocetTab: %d\n", obrazek->tab_size);
	for(int i = 0; i < obrazek->tab_size; i++){
		printf("tab: %d, vel: %d\n", i, obrazek->tab[i]->size);
		for (int j = 0; j < obrazek->tab[i]->size; j++){
			printf("hodnota: %d\n", obrazek->tab[i]->hodnoty[j]);
		}
	}
	
	/*
	for(int i = 192900; i < 193000; i++){
		printf("index: %d, hodnota: %d\n", i, obrazek->data[i]);
	}*/
	pic_recolor(obrazek);
	
	int sirka = obrazek->w;
	int vyska = obrazek->h;
	FILE* vystup;
	vystup = fopen("C:/Users/sabal/C projects/semestralka/vystup.pgm", "w");
	fprintf(vystup, "P5\n");
	fprintf(vystup, "%d %d\n", sirka, vyska);
	fprintf(vystup, "255\n");
	
	for(int i = 0; i < sirka * vyska; i++){
		fputc(obrazek->hodnoty[i], vystup);
	}
	fprintf(vystup, "\n");
	fclose(vystup);
	
	return 0;
}