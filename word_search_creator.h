/*
	HEADERS DE FUNCIONES PARA CREADOR DE SOPA DE LETRAS (word_search_creator.H)
*/
#ifndef _WORD_SEARCH_CREATOR_H
#define _WORD_SEARCH_CREATOR_H

#include "util.h"
#include <unistd.h>

char ** allocate_matrix_memory(int * N, int * M);

char ** initialize_matrix(char ** matrix, int * N, int * M);

void show_matrix(char ** matrix, int * N, int * M);

#endif