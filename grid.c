/*

  Routines creating, freeing and expanding grids
  Copyright 2003 Erik Faye-Lund aka kusma/excess

*/

#include <stdlib.h>
#include "grid.h"

/* allocate memory for the grid */
grid *grid_make(int width, int height){

	/* this will eventually be a pointer to our grid */
	grid *temp;

	/* allocate memory for the grid-structure itself*/
	temp = malloc(sizeof(grid));
	/* if we are out of memory, return a nullpointer */
	if(!temp) return NULL;

	/* now, we want the grid to be the size_of_screen/8+1 */
	temp->width = (width>>3)+1;
	temp->height = (height>>3)+1;

	/* allocate memory for the grid-data */
	temp->data = malloc(sizeof(grid_node)*temp->width*temp->height);
	if(!temp->data){
		/* oops, no more memory */
		free(temp);
		return NULL;
	}

	/* sir yes sir, returning a pointer to the grid */
	return temp;
}

/* free the previously allocated grid */
void grid_free(grid *grid){
	/* oops, a nullpointer */
	if(!grid) return;

	/* free the grid-data */
	free(grid->data);

	/* just to make sure */
	grid->data = NULL;
	grid->width = 0;
	grid->height = 0;

	/* free the grid itself */
	free(grid);
}

static void fill_quad(unsigned int* target, int width, int x, int y, grid_node *n1, grid_node *n2, grid_node *n3, grid_node *n4, unsigned int* texture){

	/*
	calculate vertical deltavalues.
	difference over the area, multiplyed with 65536 for float -> 16.16 fixedpoint
	(16 bits fractional part should be sufficient), and finally divided by 8
	(the height of the grid-node)
	*/
	int u_delta1 = (int)((n3->u-n1->u)*65536)>>3;
	int v_delta1 = (int)((n3->v-n1->v)*65536)>>3;
	int u_delta2 = (int)((n4->u-n2->u)*65536)>>3;
	int v_delta2 = (int)((n4->v-n2->v)*65536)>>3;

	/* convert to fixedpoint */
	int u1 = (int)(n1->u*65536);
	int u2 = (int)(n2->u*65536);
	int v1 = (int)(n1->v*65536);
	int v2 = (int)(n2->v*65536);

	/* offset the pointer to videomemory */
	target+= x+y*width;

	for(y=8; y; y--){
		/*
		calculate horisontal deltavalues.
		basicly the same as the vertical deltavalues, only now the values allready
		are fixedpoint
		*/
		int inner_udelta = (u2-u1)>>3;
		int inner_u = u1;
		int inner_vdelta = (v2-v1)>>3;
		int inner_v = v1;
		int counter;

		/* (this loop should really be unrolled, but that doesn't
		illustrate the point that well) */
		for(counter=8; counter; counter-- ){

			/* plot the pixel */
			*target++ = texture[((inner_u>>16)&0xFF)+((inner_v>>8)&0xFF00)];

			/* interpolate horisontally */
			inner_u+=inner_udelta;
			inner_v+=inner_vdelta;
		}

		/* interpolate vertically */
		u1+=u_delta1;
		u2+=u_delta2;
		v1+=v_delta1;
		v2+=v_delta2;

		/*
		move the pointer to the correct
		address for the next scanline. (the pointer has already been moved 8 pixels to the right
		during the horisontal interpolation)
		*/
		target+=width-8;
	}
}

/* this is the routine that draws the entire screen */
void grid_expand(unsigned int* target, int width, int height, grid* source, unsigned int *texture){
	/* set a pointer to the first element */
	grid_node *pointer = source->data;

	/* we'll use this value later */
	int w = source->width-1;
	int x,y;

	/* we want only to draw what is BETWEEN the gridnodes, so we loop width-1 */
	for(y=0; y<(source->height)-1;y++){
		for(x=0;x<w;x++){
			/*
			draw the quad.
			If you would want to draw this using hardware-rendering, just draw a quad or
			two triangles here.
			*/
			fill_quad(target, width, x<<3, y<<3,
				pointer,
				pointer+1,
				pointer+w+1,
				pointer+w+2,
				texture);
			pointer++;
		}
		pointer++;
	}

}
