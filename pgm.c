#include <stdlib.h>
#include <stdio.h>
#include "pgm.h"

void pic_color(pgm *p){
	int sirka = p->w;
	int vyska = p->h;
	int index = 0;
	int max = p->max;
	p -> tab_size = 0;
	p -> tab_first = NULL;
	p -> tab_last = NULL;
	int newColor = 20;
	int colorStep = 2;
	int sousedH, sousedL, sousedHL, sousedHP;
	for(int i = 0; i < vyska; i++){
		for(int j = 0; j < sirka; j++){
			if(p->data[index] == max){
				
				sousedH = 0;
				sousedL = 0;
				sousedHL = 0;
				sousedHP = 0;
				if(i == 0){
					if(j == 0){
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
			index++;
		}
	}
}
void add_value(int a, int b, pgm *p){
	void *temp;
	if(p -> tab_first == NULL){
		tabulka* newTab;
		newTab = (tabulka *) malloc(sizeof(tabulka));
		newTab->max_size = 50;
		newTab->hodnoty = (int *) malloc(sizeof(int) * newTab->max_size);
		newTab->hodnoty[0] = a;
		if(a == b){
			newTab->size = 1;
		}else{
			newTab->hodnoty[1] = b;
			newTab->size = 2;
		}
		newTab->next = NULL;
		newTab->prev = NULL;
		p->tab_first = newTab;
		p->tab_last = newTab;
		p->tab_size = 1;
	}else{
		tabulka *index_a, *index_b;
		tabulka* walk = p->tab_first;
		while(walk != NULL){
			for(int j = 0; j < walk->size; j++){
					if(walk->hodnoty[j] == a){
						a = 0;
						index_a = walk;
					} 
					if(walk->hodnoty[j] == b){
						b = 0;						
						index_b = walk;
					} 
			}
			walk = walk->next;
		}
		if(a != 0 && b != 0){
			tabulka* newTab;
			newTab = malloc(sizeof(tabulka));
			newTab->max_size = 50;
			newTab->hodnoty = (int *) malloc(sizeof(int) * newTab->max_size);
			newTab->hodnoty[0] = a;
			if(a == b){
			newTab->size = 1;
			}else{
			newTab->hodnoty[1] = b;
			newTab->size = 2;
			}
			newTab->next = NULL;
			
			p->tab_last->next = newTab;
			newTab->prev = p->tab_last;
			p->tab_last = newTab;
			p->tab_size++;
			return 0;
		}else if(a == 0 && b == 0){
			if(index_a != index_b){
				int vel = index_a->size;
				index_a->size += index_b->size;
				if(index_a->size >= index_a->max_size){
					index_a->max_size = index_a->size*2;
					temp = realloc(index_a->hodnoty, sizeof(int) * index_a->max_size);
					index_a->hodnoty = (tabulka *) temp;
					
				}
				for(int i = 0; i < index_b->size; i++){
					index_a->hodnoty[vel] = index_b->hodnoty[i];
					vel++;
				}
				
				if(index_b->next == NULL){
					index_b->prev->next = NULL;
					p->tab_last = index_b->prev;
				}
				else if(index_b->prev == NULL){
					index_b->next->prev = NULL;
					p->tab_first = index_b->next;
				}else{
					index_b->next->prev = index_b->prev;
					index_b->prev->next = index_b->next;
				}
				p->tab_size--;
			}
		}else{
			int vel = 0;
			if(a == 0){
				vel = index_a->size;
				index_a->size++;
				if(index_a->size >= index_a->max_size){
					index_a->max_size = index_a->size*2;					
					temp = realloc(index_a->hodnoty, sizeof(int) * index_a->max_size);
					index_a->hodnoty = (tabulka *) temp;
				}
				index_a->hodnoty[vel] = b;
				
			}else{			
				vel = index_b->size;
				index_b->size++;
				if(index_b->size >= index_b->max_size){				
					index_b->max_size = index_b->size*2;					
					temp = realloc(index_b->hodnoty, sizeof(int) * index_b->max_size);									
					index_b->hodnoty = (tabulka *) temp;
				}
				index_b->hodnoty[vel] = a;
			}
		}
	}
	return 0;
}

void pic_recolor(pgm *p){
	int sirka = p->w;
	int vyska = p->h;
	for(int i = 0; i < sirka * vyska; i++){
		int value = p->data[i];
		tabulka* walk = p->tab_first;
		int index = 0;
		while(walk != NULL){
			for(int j = 0; j < walk->size; j++){
				if(value == walk->hodnoty[j]){
					p->hodnoty[i] = walk->hodnoty[0];
				}
			}
			walk = walk->next;
			index++;
		}
	}
} 
