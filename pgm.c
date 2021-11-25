#include <stdlib.h>
#include <stdio.h>
#include "pgm.h"

void pic_color(pgm *p){
	int sirka = p->w;
	int vyska = p->h;
	int index = 0, hi = 0, iTab=0;
	int max = p->max;
	int newColor = 50;
	int hodnoty[4] = {0, 0, 0, 0};
	for(int i = 0; i < vyska; i++){
		for(int j = 0; j < sirka; j++){
			
			if(p->data[index] == max){
				
				int sousedH = 0;
				int sousedL = 0;
				int sousedHL = 0;
				int sousedHP = 0;
				if(i == 0){
					
					if(j == 0){
						//printf("1 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]);
						p->data[index] = newColor;
						newColor += 20;	
					}else{
						
						sousedL = p->data[index-1];
						if(sousedL>0){
							p->data[index] = sousedL;
						}else{
							p->data[index] = newColor;
							newColor += 20;
						}
						//printf("2 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]);
					}
				}else{
					
					sousedH = p->data[index - sirka];
					if(j == 0){
						sousedHP = p -> data[index-sirka+1];
						if(sousedHP > 0 || sousedH > 0){
							if(sousedHP > 0){
								p->data[index] = sousedHP;
								hodnoty[hi] = sousedHP;
								hi++;
							}
							if(sousedH > 0){
								p->data[index] = sousedH;
								hodnoty[hi] = sousedH;
							}
						}else{
							p->data[index] = newColor;
							newColor += 20;
						}
						//printf("3 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]);
						
					}else if(j == sirka-1){
						sousedL = p->data[index-1];
						sousedHL = p->data[index-sirka-1];
						if(sousedH > 0 || sousedHL > 0 || sousedL > 0){
							if(sousedH > 0){
								p->data[index] = sousedH;
								hodnoty[hi] = sousedH;
								hi++;
							}
							if(sousedHL > 0){
								p->data[index] = sousedHL;
								hodnoty[hi] = sousedHL;
								hi++;
							}
							if(sousedL > 0){
								p->data[index] = sousedL;
								hodnoty[hi] = sousedL;
							}
						}else{
							p->data[index] = newColor;
							newColor += 20;
						}
						//printf("5 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]); 
						
					}else{
						sousedL = p->data[index-1];
						sousedHL = p->data[index-sirka-1];
						sousedHP = p -> data[index-sirka+1];
						if(sousedH > 0 || sousedHL > 0 || sousedL > 0 || sousedHP > 0){
							if(sousedH > 0){
								p->data[index] = sousedH;
								hodnoty[hi] = sousedH;
								hi++;
							}
							if(sousedHL > 0){
								p->data[index] = sousedHL;
								hodnoty[hi] = sousedHL;
								hi++;
							}
							if(sousedHP > 0){
								p->data[index] = sousedHP;
								hodnoty[hi] = sousedHP;
								hi++;
							}
							if(sousedL > 0){
								p->data[index] = sousedL;
								hodnoty[hi] = sousedL;
							}
						}else{
							p->data[index] = newColor;
							newColor += 20;
						}
					}
				}
			}
			
			if((hodnoty[0]!=hodnoty[1] || hodnoty[0]!=hodnoty[2] || hodnoty[0]!=hodnoty[3])||
			(hodnoty[1]!=hodnoty[2] || hodnoty[1]!=hodnoty[3])||(hodnoty[2]!=hodnoty[3])){
			
			tabulka* newTab;
			newTab = (tabulka *) malloc(sizeof(tabulka));
			
			
			for(int i = 0; i < 4; i++){
				//printf("%d\n", hodnoty[i]);
				newTab->hodnoty[i] = hodnoty[i];
				printf("%d: %d\n",index,newTab->hodnoty[i]);
				hodnoty[i] = 0;
			}
			p->tab[iTab] = newTab;
			iTab++;
			}
			//printf("ind: %d, itab: %d, ok\n", index, iTab);
			index++;
			hi=0;	
		}
	}
}