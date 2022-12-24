/*

  Slow routines for blending between images
  Copyright 2003 Erik Faye-Lund aka kusma/excess

*/

#ifndef __BLEND_H__
#define __BLEND_H__

#ifdef __cplusplus
extern "C"{
#endif

void blend(unsigned int* target, unsigned int *source, int size, unsigned char alpha);
void add_blend(unsigned int* target, unsigned int *source, int size);

#ifdef __cplusplus
}
#endif

#endif /*__BLEND_H__*/
