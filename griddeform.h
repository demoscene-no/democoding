/*

  Some basic routines for manipulating the content of a grid
  Copyright 2003 Erik Faye-Lund aka kusma/excess

*/

#ifndef __GRIDDEFORM_H__
#define __GRIDDEFORM_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "grid.h"

void grid_zero(grid* grid);
void grid_flat(grid* grid, float xscroll, float yscroll);
void grid_sinus(grid* grid, float xscale, float yscale, float xoffset, float yoffset, float power);
void grid_wave(grid* grid, float scale, float anim, float power);

#ifdef __cplusplus
}
#endif

#endif /*__GRIDDEFORM_H__*/
