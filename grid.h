/*

  Routines creating, freeing and expanding grids
  Copyright 2003 Erik Faye-Lund aka kusma/excess

*/

#ifndef __GRID_H__
#define __GRID_H__

#ifdef __cplusplus
extern "C"{
#endif

typedef struct{
	float u,v;
}grid_node;

typedef struct{
	int width, height;
	grid_node *data;
}grid;

grid *grid_make(int width, int height);
void grid_expand(unsigned int* target, int width, int height, grid* source, unsigned int *texture);
void grid_free(grid *grid);

#ifdef __cplusplus
}
#endif

#endif /*__GRID_H__*/
