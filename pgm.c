#include <stdlib.h>
#include <stdio.h>
#include "pgm.h"

void pic_color(pgm *p){
	int sirka = p->w;
	int vyska = p->h;
	int index = 0, hi = 0, iTab=0;
	int max = p->max;
	p -> tab_size = 0;
	int newColor = 10;
	int hodnoty[4] = {0, 0, 0, 0};
	int colorStep = 1;
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
						newColor += colorStep;	
					}else{
						
						sousedL = p->data[index-1];
						if(sousedL>0){
							p->data[index] = sousedL;
						}else{
							p->data[index] = newColor;
							newColor += colorStep;
						}
						//printf("2 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]);
					}
				}else{
					
					sousedH = p->data[index - sirka];
					if(j == 0){
						sousedHP = p -> data[index-sirka+1];
						if(sousedHP > 0 || sousedH > 0){
							if(sousedH > 0){
								p->data[index] = sousedH;
								if(sousedHP > 0){
									add_value(sousedH, sousedHP, p);
								}
							}else{
								p->data[index] = sousedHP;
							}
						}else{
							p->data[index] = newColor;
							newColor += colorStep;
						}
						//printf("3 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]);
						
					}else if(j == sirka-1){
						sousedL = p->data[index-1];
						sousedHL = p->data[index-sirka-1];
						if(sousedH > 0 || sousedHL > 0 || sousedL > 0){
							if(sousedL > 0){
								p->data[index] = sousedL;
								if(sousedHL > 0){
									add_value(sousedL, sousedHL, p);
								}
								if(sousedH > 0){
									add_value(sousedL, sousedH, p);
								}
							}
							else if(sousedHL > 0){
								p->data[index] = sousedHL;
								if(sousedH > 0){
									add_value(sousedH, sousedHL, p);
								}
							}
							else{
								p->data[index] = sousedH;
							}
						}else{
							p->data[index] = newColor;
							newColor += colorStep;
						}
						//printf("5 - rad: %d, sl: %d, index: %d, hodnota: %d\n", i, j, index, obrazek->data[index]); 
						
					 }else{
						sousedL = p->data[index-1];
						sousedHL = p->data[index-sirka-1];
						sousedHP = p -> data[index-sirka+1];
						if(sousedH > 0 || sousedHL > 0 || sousedL > 0 || sousedHP > 0){
							if(sousedL > 0){
								p->data[index] = sousedL;
								if(sousedHL > 0){
									add_value(sousedL, sousedHL, p);
								}
								if(sousedH > 0){
									add_value(sousedL, sousedH, p);
								}
								if(sousedHP > 0){
									add_value(sousedL, sousedHP, p);
								}
							}
							else if(sousedHL > 0){
								p->data[index] = sousedHL;
								if(sousedH > 0){
									add_value(sousedHL, sousedH, p);
								}
								if(sousedHP > 0){
									add_value(sousedHL, sousedHP, p);
								}
							}
							else if(sousedH > 0){
								p->data[index] = sousedH;
								if(sousedHP > 0){
									add_value(sousedH, sousedHP, p);
								}
							}
							else{
								p->data[index] = sousedHP;	
							}
						}else{
							p->data[index] = newColor;
							newColor += colorStep;
						}
					}
				}
			}else{
				p->hodnoty[i] = 0;
			}
			/*
			if((hodnoty[0]!=hodnoty[1] || hodnoty[0]!=hodnoty[2] || hodnoty[0]!=hodnoty[3])||
			(hodnoty[1]!=hodnoty[2] || hodnoty[1]!=hodnoty[3])||(hodnoty[2]!=hodnoty[3])){
			
			//add_value(hodnoty, index);	
			
			tabulka* newTab;
			newTab = (tabulka *) malloc(sizeof(tabulka));
			newTab->hodnoty = (int *) malloc(4);
			
			for(int i = 0; i < 4; i++){
				//printf("%d\n", hodnoty[i]);
				newTab->hodnoty[i] = hodnoty[i];
				printf("%d: %d\n",index,newTab->hodnoty[i]);
			}
			p->tab[iTab] = newTab;
			iTab++;
			}
			for(int i = 0; i < 4; i++){
				hodnoty[i] = 0;
			}*/
			//printf("ind: %d, %d ok\n", index, p->tab_size);
			//printf("index: %d, val: %d\n", index, p->data[i]);
			index++;
			hi=0;	
		}
	}
}
void add_value(int a, int b, pgm *p){
	tabulka* newTab;
	if(p -> tab_size == 0 ){
		newTab = (tabulka *) malloc(sizeof(tabulka));
		newTab->hodnoty = (int *) malloc(sizeof(int) * 500);
		newTab->hodnoty[0] = a;
		newTab->hodnoty[1] = b;
		newTab->size = 2;
		p->tab[0] = newTab;
		p->tab_size = 1;
		return 0;
	}else{
		int index_a = 0, index_b = 0;
		for(int i = 0; i < p->tab_size; i++){
			for(int j = 0; j < p->tab[i]->size; j++){
				
					if(p->tab[i]->hodnoty[j] == a){
						a = 0;
						index_a = i;
					} 
					if(p->tab[i]->hodnoty[j] == b){
						b = 0;
						index_b = i;
					} 
			
			}
		}
		if(a != 0 && b != 0){
			//printf("redy");
			newTab = malloc(sizeof(tabulka));
			newTab->hodnoty = (int *) malloc(sizeof(int) * 10000);
			newTab->hodnoty[0] = a;
			newTab->hodnoty[1] = b;
			newTab->size = 2;
			p->tab[p->tab_size] = newTab;
			p->tab_size++;
			return 0;
		}else if(a == 0 && b == 0){
			if(index_a != index_b){
				//printf("redy\n");
				int tab_b = 0, tab_a = 0;
				if(index_a < index_b){
					tab_b = index_b;
					tab_a = index_a;
				}else{
					tab_b = index_a;
					tab_a = index_b;
				}
				int size_taba = p->tab[tab_a]->size;
				int size_tabb = p->tab[tab_b]->size;	
								
				for(int i = 0; i < size_tabb; i++){
					p->tab[tab_a]->hodnoty[size_taba] = p->tab[tab_b]->hodnoty[i];
					p->tab[tab_b]->hodnoty[i] = p->max+1000;
					//p->tab[tab_b]->size = 0;
					size_taba++;
				}
				
				p->tab[tab_a]->size = size_taba;
				//p->tab_size--;
			}
		}else{
			//printf("a: %d, b: %d\n", a, b);
			int vel = 0;
			//printf("vel: %d", vel);
			if(a == 0){
				vel = p->tab[index_a]->size;
				p->tab[index_a]->hodnoty[vel] = b;
				p->tab[index_a]->size++;
			}else{
				vel = p->tab[index_b]->size;
				p->tab[index_b]->hodnoty[vel] = a;
				p->tab[index_b]->size++;
			}
		}
	}
	return 0;
}

void adj_tab(pgm* p){
	int index = 0, pocet_tab = 0;
	for(int i = 0; i < p->tab_size; i++){
		if(p->tab[i]->hodnoty[0] != p->max+1000){
			p->tab[index] = p->tab[i];
			pocet_tab++;
			index++;
		}
	}
	p->tab_size = pocet_tab;
}

void pic_recolor(pgm *p){
	int sirka = p->w;
	int vyska = p->h;
	for(int i = 0; i < sirka * vyska; i++){
		int value = p->data[i];
			for(int j = 0; j < p->tab_size; j++){
				for(int k = 0; k < p->tab[j]->size; k++){
					if(value == p->tab[j]->hodnoty[k]){
						p->hodnoty[i] = p->tab[j];
					}
				}
			}
	}
} 
