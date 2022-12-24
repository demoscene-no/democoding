/*

  Slow routines for blending between images
  Copyright 2003 Erik Faye-Lund aka kusma/excess

*/

void blend(unsigned int* target, unsigned int *source, int size, unsigned char alpha){
	/*
	this is proabebly one of the best ways to blend 24bit pixels without using mmx.
	the formula is:

	final pixel = pixel1*alpha + pixel2*(1-alpha)

	this should be done seperatly on each colorchannel, but we can safely combine red and blue,
	since these channels won't mix. this saves us two muls pr pixel.
	*/
	unsigned char invert_alpha = 255-alpha;
	for(;size;size--){
		unsigned int rb;
		unsigned int g;

		/* get target-pixel */
		unsigned int old_pixel = *target;
		/* get source-pixel */
		unsigned int new_pixel = *source++;

		/*
		in order to prevent the colorchannels to mix, we seperate them into the following
		formats: 0xRR00BB and 0x00GG00 (as I sain earlier). four MUL's pr pixel isn't that bad, but mmx would
		speed this up quite a bit.
		*/

		rb = ((((new_pixel&0xFF00FF)*alpha)+((old_pixel&0xFF00FF)*invert_alpha))>>8)&0xFF00FF;
		g = ((((new_pixel&0x00FF00)*alpha)+((old_pixel&0x00FF00)*invert_alpha))>>8)&0x00FF00;

		/* combine the result */
		*target++ = rb+g;
	}
}

void add_blend(unsigned int* target, unsigned int *source, int size){
	/* using mmx to add pixels is quite easy */
	for(;size;size--){
		/* get target-pixel */
		unsigned int old_pixel = *target;
		/* get source-pixel */
		unsigned int new_pixel = *source++;
		_asm{
			/* copy target-pixel into mm0 */
			movd mm0, old_pixel
			/* add source-pixel to mm0 */
			paddusb mm0, new_pixel
			/* copy mm0 into new_pixel */
			movd new_pixel, mm0
		}
		/* update the target-buffer with the calculated value */
		*target++ = new_pixel;
	}
	_asm emms;
}