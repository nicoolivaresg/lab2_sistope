/*
	IMPLEMENTACION DE FUNCIONES PARA EL MANEJADOR DE HEBRAS (thread_handler.h)
*/

#include "thread_handler.h"
/*
int loadWordsOnThreads(FILE *file, WSThread * threads , int threads_count, int words_count){

}
*/

void * locate(void * args){
	WSThread * t = (WSThread *) args;
	/*
	int i = 0;
	char * word = NULL;
	while ( i <  t -> words_count){
		word = t -> words[i];
		printf("%s\n", word);
		i++;
	}
	*/
	printf("Ubicando\n");
}