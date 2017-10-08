/*
	HEADERS DE FUNCIONES PARA MANEJADOR DE HEBRAS
*/

#ifndef _THREAD_HANDLER_H
#define _THREAD_HANDLER_H

#include "util.h"
#include "word_search_creator.h"
#include <pthread.h>

struct WordSearchThread;

typedef struct WordSearchThread{
	int id;
	int rows, cols;
	int* posX;
	int* posY;
	int wordCount;
	char ** words;
	char *** matrix;
	pthread_t thread;
	pthread_mutex_t ** threadMutex;
} WSThread;

void WSThread_init(WSThread* wsthread, int id, int rows, int cols, int words, pthread_mutex_t* mutex, char** matrix);

void WSThread_add_word(WSThread* wsthread, char* word, int wordIndex);

void WSThread_set_coordinates(WSThread* wsthread, int x, int y, int word);

void WSThread_free(WSThread* wsthread);

void * locate(void * args);

#endif