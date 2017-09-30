#include "word_search_creator.h"
/*
	IMPLEMENTACIÓN DE FUNCIONES CREADOR DE SOPA DE LETRAS (word_search_creator.h)
*/

char ** allocate_matrix_memory(int * N, int * M){
	char ** newMatrix = malloc(	(*N) * sizeof(char*) );
	int i = 0;
	for (i = 0; i < (*N); i++)
	{
		newMatrix[i] = malloc( (*M) * sizeof(char) );
	}
	return newMatrix;
}


char ** initialize_matrix(char ** matrix, int * N, int * M){
	int i,j;
	for (i = 0; i < (*N); i++)
	{
		for (j = 0; j < (*M); j++){
			matrix[i][j] = 64;
		}
	}
	return matrix;
}

void show_matrix(char ** matrix, int * N, int * M){
	int i,j;
	for (i = 0; i < (*N); i++)
	{
		for (j = 0; j < (*M); j++){
			printf("%c", matrix[i][j]);
		}
		printf("\n");
	}
}

