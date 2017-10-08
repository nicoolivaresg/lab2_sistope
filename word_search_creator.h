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

void write_word_matrix(char*** matrix, int x, int y, char* word);

void fill_matrix(char*** matrix, int rows, int cols);

void init_positionable(int rows, int cols);

void set_positions(int rows, int cols, int x, int y, int wordLength);

int get_locatable_coordinates(int rows, int cols, int* x, int* y, int wordLength);

int can_position_in_matrix(int rows, int cols, int x, int y, int wordLength);

// Variable global que almacena si es que se puede posicionar una palabra en este lugar
extern int** positionable;

// Indica la cantidad mas larga de espacio que queda en alguna linea horizontal para
// posicionar una palabra
extern int longestEmpty;

#endif