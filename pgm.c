#include <stdlib.h>
#include <stdio.h>
#include "pgm.h"

#define def_color 20
#define color_step 1
#define def_size 50

/**
* funkce implementuje první průchod algoritmu CCL
* prochází se každý pixel obrázku po řádcích a u každého se rozhodne kolik má již přebarvených seousedů a jaká je jejich hodnota
* za každého nenulového souseda pixelu se zavolá funkce add_value a jako parametry funkce se předají, pixel, který zrovna procházíme a tento jeho nenulový soused
*/
void pic_color(pgm *p){
	int sirka = p->w;
	int vyska = p->h;
	int index = 0;
	int max = p->max;
	
	p -> tab_size = 0;
	p -> tab_first = NULL;
	p -> tab_last = NULL;
	
	int newColor = def_color;
	int colorStep = color_step;
	int sousedH, sousedL, sousedHL, sousedHP;
	int i, j;
	
	/* sanity check */
	if(p == NULL){
		return;
	}
	
	for(i = 0; i < vyska; i++){
		for(j = 0; j < sirka; j++){
			if(p->data[index] == max){
				
				/* defaultně se očekává, že sousedé pixelu budou součástí pozadí */
				sousedH = 0;
				sousedL = 0;
				sousedHL = 0;
				sousedHP = 0;
				
				/* první pixel v prvním řádku */
				if(i == 0){
					if(j == 0){
						p->data[index] = newColor;
						newColor += colorStep;	
						
					/* ostatní pixely v prvním řádku */	
					}else{
						sousedL = p->data[index-1];
						if(sousedL>0){
							p->data[index] = sousedL;
						}else{
							p->data[index] = newColor;
							newColor += colorStep;
						}
					}
					
				/* pixely v prvním sloupci */
				}else{
					/* pixely v prvním sloupci */
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
					
					/* pixely v posledním sloupci */	
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
						
				     /* všechny ostatní pixely */
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
			/* pixel je součást pozadí, můžeme zaznamenat do finálního pole */	
			}else{
				p->hodnoty[i] = 0;
			}
			index++;
		}
	}
}

/**
* a, b - 2 hodnoty mezi kterými došlo ke kolizi
* funkce zjistí, zda se nějaká ze dvou hodnot nachází v nějaké kolizní množině
* pokud ne tak založí novou množinu a přidá tam obě hodnoty pokud jsou rozdílné, pokud ne, tak přidá jen jednu
* pokud se v nějaké množině nachází jen jedna z hodnot, tak do stejné množiny přidá i druhou hodnotu
* pokud se hodnoty nachází v jiných množinách, tak se hodnoty jedné množiny překopírují do druhé a ta první se odstraní ze spojového seznamu 
*/
void add_value(int a, int b, pgm *p){
	
	int j;
	void *temp;
	
	/* sanity check */
	if(p == NULL || (a <= 0 || b <= 0 )){
		return;
	}
	
	/* v kolizní tabulce zatím nejsou žádné hodnoty */
	if(p -> tab_first == NULL){
		tabulka* newTab;
		newTab = (tabulka *) malloc(sizeof(tabulka));
		newTab->max_size = def_size;
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
		
		/* průchod kolizní tabulky a zjištění, zda se v nějaké množině nachází hodnoty a nebo b */
		while(walk != NULL){
			for(j = 0; j < walk->size; j++){
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
		
		/* hodnoty a,b v kolizní tabulce nejsou a musí se založit nová množina */
		if(a != 0 && b != 0){
			tabulka* newTab;
			newTab = malloc(sizeof(tabulka));
			newTab->max_size = def_size;
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
		
		/* hodnoty se nachází v jiných množinách, jednu překopírujeme do druhé */	
		}else if(a == 0 && b == 0){	
			if(index_a != index_b){
				int vel = index_a->size;
				index_a->size += index_b->size;
				
				/* pole se nevejde do místa alokovaného v paměti */
				if(index_a->size >= index_a->max_size){
					index_a->max_size = index_a->size*2;
					temp = realloc(index_a->hodnoty, sizeof(int) * index_a->max_size);
					index_a->hodnoty = temp;	
				}
				for(int i = 0; i < index_b->size; i++){
					index_a->hodnoty[vel] = index_b->hodnoty[i];
					vel++;
				}
				
				/* odstranění množiny ze spojového seznamu */
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
				free(index_b->hodnoty);
				free(index_b);
				p->tab_size--;
			}
			
		/* v tabulce je jen jedna hodnota, druhá se musí přidat */	
		}else{
			int vel = 0;
			if(a == 0){
				vel = index_a->size;
				index_a->size++;
				
				/* pole se nevejde do místa alokovaného v paměti */
				if(index_a->size >= index_a->max_size){
					index_a->max_size = index_a->size*2;					
					temp = realloc(index_a->hodnoty, sizeof(int) * index_a->max_size);
					index_a->hodnoty = temp;
				}
				index_a->hodnoty[vel] = b;
				
			}else{			
				vel = index_b->size;
				index_b->size++;
				
				/* pole se nevejde do místa alokovaného v paměti */
				if(index_b->size >= index_b->max_size){				
					index_b->max_size = index_b->size*2;					
					temp = realloc(index_b->hodnoty, sizeof(int) * index_b->max_size);									
					index_b->hodnoty = temp;
				}
				index_b->hodnoty[vel] = a;
			}
		}
	}
}

/**
* funkce implementuje druhý průchod algoritmu CCL
* každé množině v kolizní tabulce postupně přiřadí novou hodnotu, první hodnotu z množiny, pokud to jde
* k tomu využívá pole used_colors a funkci duplicates
* prochází pole data a pro každou hodnotu zkopíruje do pole hodnoty příslušnou barvu z pole used_colors
*/
void pic_recolor(pgm *p){
	pixel *used_colors;
	used_colors = malloc(sizeof(pixel) * p->tab_size);
	int sirka = p->w;
	int vyska = p->h;
	int index, i, j;
	
	/* sanity check */
	if(p == NULL){
		return;
	}
	
	/* hodnoty v poli použitých odstínů jsou defaultně nulové */
	for(i = 0; i < p->tab_size; i++){
		used_colors[i] = 0;
	}
	
	for(i = 0; i < sirka * vyska; i++){
		index = 0;
		int value = p->data[i];
		tabulka* walk = p->tab_first;
		
		while(walk != NULL){
			for(j = 0; j < walk->size; j++){
				if(value == walk->hodnoty[j]){
					if(used_colors[index] == 0){
						/* oblasti ještě není v poli použitých odstínů žádný přiřazen*/
						used_colors[index] = walk->hodnoty[0];
						while(duplicates(used_colors, p->tab_size)){
							used_colors[index] += 1;
							
							/* pokud je splněna podmínka, tak už neexistuje hodnota unsigned charu, která by nebyla použita */
							if(used_colors[index] > p->max * 2){
								perror("ERROR: picture has more contiguous areas than the color range is!!!!!........");
								return;
							}
						}
					}
					p->hodnoty[i] = used_colors[index];
				}
			}
			walk = walk->next;
			index++;
		}
	}
	free(used_colors);	
}

/**
* colors - pole hodnot, size - jeho velikost
* funkce projde pole colors a zjistí, zda se v něm nějaká hodnota kromě nuly vyskytuje dvakrát
*/
int duplicates(pixel* colors, int size){
	/* pokud je splněna tato podmínka, nemohou být v poli stejné hodnoty */ 
	if(size < 1 && colors == NULL){
		return 0;
	}else{
		int i, j;
		for(i = 0; i < size-1; i++){
			for(j = i+1; j < size; j++){
				if(colors[i] == colors[j] && (colors[i] != 0 || colors[j] != 0)){
					return 1;
				}
			}		
		}
		return 0;
	}
} 