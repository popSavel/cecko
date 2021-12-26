#ifndef __PGM_H__
#define __PGM_H__
#include "tabulka.h"

typedef unsigned char pixel;

typedef struct pgm {
      int w, h, max;
      
      /* počet množin v tabulce kolizí */
      int tab_size;
      
      /* pole hodnot, které se prochází a mění v prvním průchodu algoritmu */
      int* data;
      
      /* pole hodnot, kam se ukládají při druhém průchodu algoritmu již finální hodnoty pixelů */
      pixel* hodnoty;
      
      /* ukazatel na první a poslední prvek spojového seznamu */
      tabulka* tab_first;
      tabulka* tab_last;
} pgm;
    
void pic_color(pgm *p);

void add_value(int a, int b, pgm *p);
    
void pic_recolor(pgm *p);    

int duplicates(pixel* colors, int size);
    
#endif    