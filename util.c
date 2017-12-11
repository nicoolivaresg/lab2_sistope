/*
	IMPLEMENTACION DE FUNCIONES DE UTILIDAD (util.h)
*/
#include "util.h"

int getDigits(int number)
{
	int digits = 1;
	int temp_number = number;
	while(temp_number >= 10) {
		temp_number /= 10;
		digits++;
	}

	return digits;
}

char* intToString(int number)
{
	int digits = getDigits(number);

	char* str = (char*)malloc(digits+1);
	snprintf(str, digits+1, "%d", number);

	return str;
}

int count_input_words(FILE * file){
	long int lines = 0, letters = 0;
	char letter = 0;
	fseek(file, 0, SEEK_SET);
	while(fscanf(file, "%c", &letter) == 1) {
		if(letter == '\n') {
			lines++;
			letters = 0;
		} else {
			letters++;
		}
	}
	if(letters > 0) lines++;
	fseek(file, 0, SEEK_SET);
	return (int) lines;
}


char* next_word(FILE* file) 
{
	char buffer[256];
	fscanf(file, "%255[^\n]%*c", buffer);

	int len = strlen(buffer);
	char* word = malloc((len+1) * sizeof(*word));
	strcpy(word, buffer);

	return word;
}

char get_random_char() {
	return (char)(rand()%((int)'z' - (int)'a' + 1) + (int)'a');
}

