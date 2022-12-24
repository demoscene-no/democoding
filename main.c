#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <math.h>

#include "leepra.h"
#include "image.h"
#include "grid.h"
#include "griddeform.h"
#include "blend.h"

/* a standard way to spit errormessages */
void error(char *error){
	MessageBox(NULL,error,NULL,MB_OK);
	exit(1);
}

/* configurations */
#define WIDTH 320
#define HEIGHT 240
#ifdef _DEBUG
#define FULLSCREEN FALSE
#else
#define FULLSCREEN TRUE
#endif

/* screenmemory */
unsigned int screen[WIDTH*HEIGHT];

void main(){
	MSG message;
	unsigned int *texture;
	unsigned int *image;
	unsigned int *text;
	grid *grid;

	/* load texture */
	if(!image_load("texture.jpg",&texture,NULL,NULL))
		error("could not load texture");

	/* load an image for the blending */
	if(!image_load("image.jpg",&image,NULL,NULL))
		error("could not load texture");

	/* load an additive textlayer */
	if(!image_load("text.jpg",&text,NULL,NULL))
		error("could not load texture");

	/* open window */
	if(!leepra_open("software rendering examplecode by kusma/excess",WIDTH,HEIGHT,FULLSCREEN))
		error("could not initialize directdraw");

	/* initialize grid */
	grid = grid_make(WIDTH,HEIGHT);

	do{
		/*
		first of all, we want the timer to be our animation-value in as many cases
		as possible. preferably all. this timer-routine gives us crap resoulution, but
		is sufficient for our current needs.
		*/
		float time = (float)GetTickCount()*0.001f;

		/* fist we start off by clearing the grid with a flat-routine */
		grid_flat(grid,time*100,(float)sin(time*0.1f)*150);

		/* then we add some turbulence */
		grid_sinus(grid, 0.3f,0.3f, -time*0.5f, -time*0.5f, 30);

		/* and we finalize with a cute "ripple"-routine */
		grid_wave(grid, 0.2f, time*3, 8);

		/* then we draw the thing */
		grid_expand(screen, WIDTH, HEIGHT, grid, texture);

		blend(screen, image, WIDTH*HEIGHT, (unsigned char)((1+sin(time))*127));
		add_blend(screen, text, WIDTH*HEIGHT);

		/* update the screen */
		leepra_update(screen);

		/* check for windowmessages */
		while(PeekMessage(&message,NULL,0,0,PM_REMOVE)){
			TranslateMessage(&message);
			DispatchMessage(&message);
		    if(message.message == WM_QUIT) break;
		}
		/* check for quitmessages and escape */
	}while(message.message!=WM_QUIT && !GetAsyncKeyState(VK_ESCAPE));

	/* uninit grid */
	grid_free(grid);

	/* free images loaded */
	free(texture);
	free(image);
	free(text);

	/* close screen */
	leepra_close();
}