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
	long int lines = 0;
	char letter = 0;
	fseek(file, 0, SEEK_SET);
	while(fscanf(file, "%c", &letter) == 1) {
		if(letter == '\n') {
			lines++;
		}
	}
	fseek(file, 0, SEEK_SET);
	return (int) lines;
}





