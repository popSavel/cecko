#ifndef __PGM_H__
#define __PGM_H__
#include "tabulka.h"

typedef unsigned char pixel;

typedef struct pgm {
      int w;
      int h;
      int max;
      pixel* data;
      tabulka** tab;
} pgm;
    
void pic_color(pgm *p);
    
#endif    