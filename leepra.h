/*

  Routines for handling directdraw and window-routines
  Copyright 2003 Erik Faye-Lund aka kusma/excess

*/

#ifndef __LEEPRA_H__
#define __LEEPRA_H__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef __cplusplus
extern "C"{
#endif

int leepra_open( char* title, int width, int height, BOOL fullscreen);
HWND leepra_get_window();
void leepra_update( void* data );
void leepra_close();

#ifdef __cplusplus
}
#endif

#endif /* __LEEPRA_H__ */