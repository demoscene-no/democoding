/*

  Just a simple filewrapper so that it's easy to include support for datafiles etc
  Copyright 2003 Erik Faye-Lund aka kusma/excess

*/

#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


file* file_open( char *filename ){
	char buffer[256];
	FILE *fp;

	file* temp = (file*)malloc( sizeof(file) );

	sprintf(buffer,"data/%s", filename);

	fp = fopen(buffer, "rb");
	if(fp==NULL){
#ifdef _DEBUG
		printf("could not open file: \"%s\"\n",buffer);
#endif 
		free(temp);
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	temp->size = ftell(fp);
	rewind(fp);

	temp->data = malloc(sizeof(unsigned char)*temp->size);
	if(!temp->data){
#ifdef _DEBUG
		printf("out of memory");
#endif 
		free(temp);
		return NULL;
	}

	fread( temp->data, sizeof(unsigned char), temp->size, fp );
	fclose(fp);

	temp->pos = 0;
	return temp;
}

int file_close(file* file){
	free(file->data);
	file->data = 0;
	file->size = 0;
	file->pos = 0;
	free(file);
	file = NULL;

	return 0;
}

int file_tell( file *file ){
	return file->pos;
}

size_t file_read( void *buffer, size_t size, size_t number, file *file ){
	unsigned int counter;
	for( counter=0; counter<(unsigned int)number; counter++ ){
		if((file->pos+size)>file->size) return counter;
		memcpy( (char*)buffer+(counter*size), file->data+file->pos, size );
		file->pos += size;
	}
	return number;
}

int file_seek( file *file, __int64 offset, int mode ){
	switch( mode ){
		case SEEK_SET:
			file->pos = (unsigned int)offset;
		break;
		case SEEK_CUR:
			file->pos += (unsigned int)offset;
		break;
		case SEEK_END:
			file->pos = file->size-(unsigned int)offset;
		break;
	}
	return 0;
}
