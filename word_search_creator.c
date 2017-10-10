#include "word_search_creator.h"
/*
	IMPLEMENTACIÓN DE FUNCIONES CREADOR DE SOPA DE LETRAS (word_search_creator.h)
*/

int** positionable = NULL;
int longestEmpty;

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

void write_word_matrix(char*** matrix, int x, int y, char* word) {
	int i, wordLength = strlen(word);
	for (int i = 0; i < wordLength; ++i)
	{
		*(matrix[y][x+i]) = toupper(word[i]);
	}
}

void fill_matrix(char*** matrix, int rows, int cols) {
	int i, j;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			if( *(matrix[i][j]) == '@') {
				*(matrix[i][j]) = get_random_char();
			}
		}
	}
}

void init_positionable(int rows, int cols) 
{
	positionable = malloc(rows * sizeof(*positionable));
	int i, j;
	for (i = 0; i < rows; ++i)
	{
		positionable[i] = malloc(cols * sizeof(*(positionable[i])));
	}

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++){
			positionable[i][j] = TRUE;
		}
	}

	longestEmpty = cols;
}

void set_positions(int rows, int cols, int x, int y, int wordLength)
{
	int i, j;
	for (i = 0; i < wordLength; ++i)
	{
		positionable[y][x + i] = FALSE;
	}

	longestEmpty = 0;
	for(i = 0; i < rows; i++) {
		int lEmpty = 0;
		for(j = 0; j < cols; j++) {
			if(positionable[i][j] == TRUE) {
				lEmpty++;
			} else {
				longestEmpty = (lEmpty > longestEmpty) ? lEmpty : longestEmpty;
				lEmpty = 0;
			}
		}
		longestEmpty = (lEmpty > longestEmpty) ? lEmpty : longestEmpty;
	}
}


int get_locatable_coordinates(int rows, int cols, int* x, int* y, int wordLength)
{
	int tempX, tempY;
	do {
		tempX = rand()%(cols);
		tempY = rand()%(rows);
		if(longestEmpty < wordLength) {
			return 1;
		}
	} while(can_position_in_matrix(rows, cols, tempX, tempY, wordLength) == FALSE);

	*x = tempX;
	*y = tempY;
	return 0;
}

int can_position_in_matrix(int rows, int cols, int x, int y, int wordLength)
{
	if(x + wordLength > cols) {
		return FALSE;
	} else {
		int i;
		for(i = 0; i < wordLength; i++) {
			if(positionable[y][x + i] == FALSE) {
				return FALSE;
			}
		}

		return TRUE;
	}
}

