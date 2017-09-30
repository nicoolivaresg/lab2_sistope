/*
	HEADERS DE FUNCIONES DE UTILIDAD
	Son funciones que son utilizadas por ambos procesos.
*/
#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/**
 * Funcion que obtiene la cantidad de digitos que tiene un numero.
 *
 * Entrada:
 *	number - Numero entero del cual se le quiere contar los digitos.
 *
 * Salida: Cantidad de digitos que tiene number.
 */
int digits(int number);

/**
 * Funcion que transforma un numero entero a string.
 *
 * Entrada:
 *	number - Numero que se quiere convertir.
 *
 * Salida: String de number.
 */
char* intToString(int number);


#endif