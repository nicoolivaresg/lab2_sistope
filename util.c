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

