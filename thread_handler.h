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
	int id;			/* Identificador para la hebra que use esta estructura. */
	int rows, cols;	/* Filas y columnas de la matriz de caracteres. */
	int* posX;		/* Coordenadas en el eje Y para cada palabra. */
	int* posY;		/* Coordenadas en el eje Y para cada palabra. */
	int wordCount;	/* Cantidad de palabras que debe posicionar esta 'hebra'. */
	char ** words;	/* Palabras que se deben posicionar. */
	char *** matrix;	/* Puntero a la matriz en donde se deben posicionar las palabras. */
	pthread_t thread;	/* Hilo que se usa para crear la hebra. */
	pthread_mutex_t ** threadMutex;	/* Arreglo de mutex con tamaño de filas.
		Como cada palabra se posiciona horizontalmente, cada hilo puede entrar a cada fila
		de la matriz sin causar problemas de sincronizacion. */
} WSThread;

/**
 * Funcion que inicializa una estructura del tipo WSThread de acuerdo a los parametros utilizados
 * con todas las alocaciones de memoria necesarias para su correcto funcionamiento.
 *
 * Entrada:
 *	wsthread- Puntero a un WSThread, estructura en donde se inicializaran los datos.
 *	id 		- Identificador del hilo que se crea.
 *	rows 	- Filas que tiene la matriz.
 *	cols 	- Columnas que tiene la matriz.
 *	words 	- Palabras de las que se debe encargar este hilo.
 *	mutex 	- Arreglo de mutex inicializados, se crea un puntero de punteros que apunta a cada valor
 *		dentro del arreglo mutex para que cada hebra tenga acceso a todos los mutex.
 *	matrix	- Matriz de caracteres, se crea un puntero a cada posicion de la matriz para que cada hebra
 *		pueda acceder y modificar la matriz original. De esta forma se pueden insertar las palabras.
 */
void WSThread_init(WSThread* wsthread, int id, int rows, int cols, int words, pthread_mutex_t* mutex, char** matrix);

/**
 * Inserta una palabra en WSThread.words en el indice indicado por el parametro
 * wordIndex, esta funcion debe utilizarse en un ciclo a travez de WSThread.wordCount
 * para evitar pasarse el indice del arreglo.
 * 
 * Entrada:
 *	wsthread 	- Puntero a WSThread en donde se guarda la palabra.
 *	word 		- Palabra que se agrega.
 *	wordIndex 	- Indice en donde se almacena la palabra dentro de la estructura.
 */
void WSThread_add_word(WSThread* wsthread, char* word, int wordIndex);

/**
 * Funcion que almacena las coordenadas x, y en los arreglos posX y posY de una variable
 * de la estructura WSThread.
 * 
 * Entrada:
 *	wsthread- Puntero a WSThread en donde se guardan las coordenadas.
 * 	x 		- Coordenada X (columna).
 *	y 		- Coordenada Y (fila).
 *  word 	- Indice en los arreglos posX y posY.
 */
void WSThread_set_coordinates(WSThread* wsthread, int x, int y, int word);

/**
 * Funcion que libera la memoria utilizada por una variable del tipo WSThread.
 * 
 * Entrada:
 *	wsthread - Puntero a variable del tipo WSThread en la cual se libera la memoria.
 */
void WSThread_free(WSThread* wsthread);

/**
 * Funcion que se usa con pthread_create para crear un hilo, se le debe entregar como
 * parametro un puntero a una estructura WSThread inicializada.
 * Entrada:
 *	args	- puntero a estructura WSThread.
 */
void * locate(void * args);


#endif