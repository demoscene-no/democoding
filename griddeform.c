/*

  Some basic routines for manipulating the content of a grid
  Copyright 2003 Erik Faye-Lund aka kusma/excess

*/

#include <math.h>
/* tell msvc to inline sin() and cos() */
#pragma intrinsic(sin,cos)

#include "grid.h"

void grid_flat(grid* grid, float xscroll, float yscroll){
	float xscale = 256.f/(grid->width);
	float yscale = 256.f/(grid->height);
	int x,y;
	grid_node *pointer = grid->data;
	for(y=0;y<grid->height;y++)
		for(x=0;x<grid->width;x++){
			pointer->u = (x*xscale)+xscroll;
			pointer->v = (y*yscale)+yscroll;
			pointer++;
		}
}

void grid_zero(grid* grid){
	int x,y;
	grid_node *pointer = grid->data;
	for(y=0;y<grid->height;y++)
		for(x=0;x<grid->width;x++){
			pointer->u = 0;
			pointer->v = 0;
			pointer++;
		}
}

void grid_wave(grid* grid, float scale, float anim, float power){
	int x,y;
	float wh = ((float)grid->width/2);
	float hh = ((float)grid->height/2);
	grid_node *pointer = grid->data;
	for(y=0;y<grid->height;y++)
		for(x=0;x<grid->width;x++){
			float cx = x-wh;
			float cy = y-hh;
			float dist = (float)sqrt(cx*cx+cy*cy);
			float mul = (1+(float)cos(dist*scale-anim))*power;
			pointer->u += cx*mul;
			pointer->v += cy*mul;
			pointer++;
		}
}

void grid_sinus(grid* grid, float xscale, float yscale, float xoffset, float yoffset, float power){
	int x,y;
	grid_node *pointer = grid->data;
	for(y=0;y<grid->height;y++)
		for(x=0;x<grid->width;x++){
			pointer->u += (float)sin(y*yscale+yoffset)*power;
			pointer->v += (float)sin(x*xscale+xoffset)*power;
			pointer++;
		}
}
