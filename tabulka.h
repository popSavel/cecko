#ifndef __TABULKA_H__
#define __TABULKA_H__

typedef struct tabulka {
	int size, max_size;
    int* hodnoty;
    struct tabulka* next;
    struct tabulka* prev;
} tabulka;
    
#endif    