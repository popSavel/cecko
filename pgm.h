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
      tabulka** tab;
} pgm;
    
void pic_color(pgm *p);

void add_value(int a, int b, pgm *p);

void adj_tab(pgm* p);
    
void pic_recolor(pgm *p);    
    
#endif    