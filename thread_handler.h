/*
	HEADERS DE FUNCIONES PARA MANEJADOR DE HEBRAS
*/

#ifndef _THREAD_HANDLER_H
#define _THREAD_HANDLER_H

#include "util.h"
#include <pthread.h>

struct WordSearchThread;

typedef struct WordSearchThread{
	pthread_t thread;
	pthread_mutex_t thread_mutex;
	int id;
	int posX;
	int posY;
	int words_count;
	char ** words;
}WSThread;

void * locate(void * args);

#endif