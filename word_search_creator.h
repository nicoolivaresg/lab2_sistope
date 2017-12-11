/*
	HEADERS DE FUNCIONES PARA CREADOR DE SOPA DE LETRAS (word_search_creator.H)
*/
#ifndef _WORD_SEARCH_CREATOR_H
#define _WORD_SEARCH_CREATOR_H

#include "util.h"
#include <unistd.h>

/**
 * Funcion que aloca la memoria necesaria para crear una matriz de tamaño
 * N x M, (Filas x columnas) y la retorna.
 * 
 * Entrada:
 *	N	- Puntero a un entero con la cantidad de filas de la matriz.
 *  M 	- Puntero a un entero con la cantidad de columnas de la matriz.
 * 
 * Salida: Matriz de tamaño N x M.
 */
char ** allocate_matrix_memory(int * N, int * M);

/**
 * Funcion que recibe una matriz de caracteres y la rellena con el caracter
 * especial '@' para luego retornarla.
 * 
 * Entrada:
 *	matrix  - Matriz de caracteres.
 *	N		- Puntero a un entero con la cantidad de filas de la matriz.
 *  M 		- Puntero a un entero con la cantidad de columnas de la matriz.
 * 
 * Salida: Matriz rellenada con el caracter especial '@'.
 */
char ** initialize_matrix(char ** matrix, int * N, int * M);

/**
 * Imprime una matriz de caracteres en la consola.
 * 
 * Entrada:
 *	matrix - Matriz a imprimir en consola.
 *	N		- Puntero a un entero con la cantidad de filas de la matriz.
 *  M 		- Puntero a un entero con la cantidad de columnas de la matriz.
 */
void show_matrix(char ** matrix, int * N, int * M);

/**
 * Escribe una palabra word, desde la posicion (x, y) en una matriz
 * 
 * Entrada:
 *	matrix 	- Puntero a una matriz de caracteres en donde se escribe la palabra.
 *	x 		- Coordenada X (columna) de la matriz desde donde se escribe la 
 				palabra (hasta x + largo palabra - 1).
 *	y 		- Coordenada Y (fila) de la matriz en donde se escribe la palabra.
 *	word 	- Palabra que se escribe en la matriz.
 */
void write_word_matrix(char*** matrix, int x, int y, char* word);

/**
 * Cambia los caracteres especiales '@' que quedan en la matriz por una letra
 * mayuscula aleatoria (por medio de la funcion get_random_char() en util).
 * 
 * Entrada:
 *	matrix 	- Puntero a una matriz de caracteres. Debe ser creada con cuidado
 *				porque cada casilla debe apuntar a la casilla de la matriz original.
 * 	rows 	- Cantidad de filas en la matriz.
 *	cols 	- Cantidad de columnas en la matriz.
 */
void fill_matrix(char*** matrix, int rows, int cols);

/**
 * Aloca espacio e inicializa las variables globales positionable y longestEmpty,
 * de acuerdo a los tamaños de la matriz (sopa de letras) que se quiere utilizar.
 * 
 * Entrada:
 * 	rows 	- Cantidad de filas en la matriz.
 *	cols 	- Cantidad de columnas en la matriz.
 */
void init_positionable(int rows, int cols);

/**
 * Utilizando la variable global positionable, indica que las casillas en donde
 * se posiciona la palabra estan ocupadas para que no sean utilizadas por otra hebra.
 * Tambien actualiza el valor de la variable global longestEmpty.
 * 
 * Entrada:
 * 	rows 		- Cantidad de filas en la matriz.
 *	cols 		- Cantidad de columnas en la matriz.
 *	x 			- Coordenada X desde donde comienza la palabra.
 *	y 			- Coordenada Y donde se quiere colocar la palabra.
 *	wordLength	- Largo de la palabra que se quiere colocar.
 */
void set_positions(int rows, int cols, int x, int y, int wordLength);

/**
 * Obtiene coordenadas (x, y) en donde se puede colocar una palabra sin problemas,
 * se debe usar muter_trylock() con estas coordenadas en el caso que otra hebra aun
 * no haya cambiado los valores de positionable pero haya logrado entrar a la seccion
 * critica. Tambien comprueba que sea posible colocar una palabra de largo wordLength
 * en una matriz de tamaño rows x cols utilizando la varible global longestEmpty.
 * 
 * Entrada:
 * 	rows 		- Cantidad de filas en la matriz.
 *	cols 		- Cantidad de columnas en la matriz.
 *	x 			- Puntero a coordenada X desde donde comienza la palabra.
 *	y 			- Puntero a coordenada Y donde se quiere colocar la palabra.
 *	wordLength	- Largo de la palabra que se quiere colocar.
 * 
 * Salida: 0 en caso de que funcion correctamente y 1 en caso que sea imposible colocar
 * una palabra de largo wordLength en la matriz.
 */
int get_locatable_coordinates(int rows, int cols, int* x, int* y, int wordLength);

/**
 * Indica si es que se puede colocar una palabra de largo wordLength en las 
 * coordenadas (x,y), en una matriz de tamaño rows x cols sin que sobreescriba otra
 * palabra o que se pase del tamaño de la matriz.
 * Esto lo realiza utilizando la variable global positionable.
 * 
 * Entrada:
 * 	rows 		- Cantidad de filas en la matriz.
 *	cols 		- Cantidad de columnas en la matriz.
 *	x 			- Coordenada X desde donde se quiere que comienze la palabra.
 *	y 			- Coordenada Y donde se quiere colocar la palabra.
 *	wordLength	- Largo de la palabra que se quiere colocar.
 * 
 * Salida: TRUE (1) en caso de que sea posible y FALSE (0) en otros casos.
 */
int can_position_in_matrix(int rows, int cols, int x, int y, int wordLength);


// Variable global que almacena si es que se puede posicionar una palabra en este lugar
extern int** positionable;

// Indica la cantidad mas larga de espacio que queda en alguna linea horizontal para
// posicionar una palabra, se re-calcula este valor cada vez que se inserta una palabra
// en la matriz, ya que es en este momento en el que esta variable deberia cambiar.
extern int longestEmpty;

#endif