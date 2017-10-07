/*
	IMPLEMENTACION DE FUNCIONES PARA EL MANEJADOR DE HEBRAS (thread_handler.h)
*/

#include "thread_handler.h"
/*
int loadWordsOnThreads(FILE *file, WSThread * threads , int threads_count, int wordCount){

}
*/

void WSThread_init(WSThread* wsthread, int id, int rows, int cols, int words, pthread_mutex_t* mutex)
{
	int i;

	wsthread->id = id;
	wsthread->rows = rows;
	wsthread->cols = cols;
	wsthread->wordCount = words;

	wsthread->threadMutex = malloc(rows * sizeof(*(wsthread->threadMutex)));
	for (int i = 0; i < rows; ++i)	{
		wsthread->threadMutex[i] = &(mutex[i]);

	}

	wsthread->posX = malloc(words * sizeof(*(wsthread->posX)));
	wsthread->posY = malloc(words * sizeof(*(wsthread->posY)));
	wsthread->words = malloc(words * sizeof(*(wsthread->words)));
}

void WSThread_add_word(WSThread* wsthread, char* word, int wordIndex)
{
	wsthread->words[wordIndex] = word;
}

void WSThread_set_coordinates(WSThread* wsthread, int x, int y, int word)
{
	wsthread->posX[word] = x;
	wsthread->posY[word] = y;
}

void WSThread_free(WSThread* wsthread)
{
	free(wsthread->posX);
	free(wsthread->posY);
	for (int i = 0; i < wsthread->wordCount; ++i)
	{
		free(wsthread->words[i]);
	}
	free(wsthread->words);
}

void * locate(void * args) {
	WSThread * t = (WSThread *) args;
	int i;

	// Inicializar semilla random
	srand(time(NULL) * t->id);

	for (i = 0; i < t->wordCount; ++i)
	{
		char* word = t->words[i];
		int lenWord = (int)strlen(word);
		do {
			int rc = get_locatable_coordinates(t->rows, t->cols, &(t->posX[i]), &(t->posY[i]), lenWord);
			printf("%d %d %d\n", t->id, t->posX[i], t->posY[i]);
			// Revisar si es que es posible poner esta palabra en algun lugar para que
			// no se produzca un ciclo infinito.
		} while(pthread_mutex_trylock(t->threadMutex[t->posY[i]]) != 0);

		printf("seccion critica: %d\n", t->id);
		int k;
		for (int k = 0; k < 100000000; ++k);
		set_positions(t->posX[i], t->posY[i], lenWord);

		pthread_mutex_unlock(t->threadMutex[t->posY[i]]);
	}

	printf("Ubicando\n");
}