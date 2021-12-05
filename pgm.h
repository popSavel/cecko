#ifndef __PGM_H__
#define __PGM_H__
#include "tabulka.h"

typedef unsigned char pixel;

typedef struct pgm {
      int w;
      int h;
      int max;
      int tab_size;
      int* data;
      pixel* hodnoty;
      tabulka* tab_first;
      tabulka* tab_last;
} pgm;
    
void pic_color(pgm *p);

void add_value(int a, int b, pgm *p);
    
void pic_recolor(pgm *p);    
    
#endif    