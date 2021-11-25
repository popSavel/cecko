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
	
	obrazek->data = (pixel*) malloc(sizeof(pixel) * velikost);
	obrazek->tab = (tabulka**) malloc(sizeof(tabulka) * 10000);
	for(int i = 0; i < velikost; i++){
		x = fgetc(f);
		obrazek->data[i] = x;
		//printf("%d: %d\n",i,  obrazek->data[i]);
	}
	
	pic_color(obrazek);
	
	/*
	int sirka = obrazek->w;
	int vyska = obrazek->h;
	int index = 0;
	int max = obrazek->max;
	for(int i = 0; i < vyska; i++){
		for(int j = 0; j < sirka; j++){
			if(i == 0){
				if(j == 0){
					printf("1 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]);
				}else{
					printf("2 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]);
				}
			}else{
				if(j == 0){
					printf("3 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]);
				}else if(j == sirka-1){
					printf("5 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]);
				}else{
					printf("4 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]);
				}
			}
			index++;	
		}
	}*/
	for(int i = 0; i < 100; i++){	
			printf("%d: %d, %d, %d, %d\n", i, obrazek->tab[i]->hodnoty[0], obrazek->tab[i]->hodnoty[1], obrazek->tab[i]->hodnoty[2], obrazek->tab[i]->hodnoty[3]);
	}
	
	int sirka = obrazek->w;
	int vyska = obrazek->h;
	FILE* vystup;
	vystup = fopen("C:/Users/sabal/C projects/semestralka/vystup.pgm", "w");
	fprintf(vystup, "P5\n");
	fprintf(vystup, "%d %d\n", sirka, vyska);
	fprintf(vystup, "255\n");
	
	for(int i = 0; i < sirka * vyska; i++){
		fputc(obrazek->data[i], vystup);
	}
	fprintf(vystup, "\n");
	fclose(vystup);
	
	return 0;
}