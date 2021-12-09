#ifndef __TABULKA_H__
#define __TABULKA_H__

typedef struct tabulka {
	
	/* size - počet prvků v poli hodnoty, max_size - maximální počet prvků v poli hodnoty, po překročení se reallocuje paměť */
	int size, max_size;
	
	/* pole hodnot, mezi kterými došlo ke kolizi */
    int* hodnoty;
    
    /* ukazatel na předchozí a následující prvek ve spojovém seznamu */
    struct tabulka* next;
    struct tabulka* prev;
    
} tabulka;
    
#endif    