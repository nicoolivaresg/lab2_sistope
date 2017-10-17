#include "thread_handler.h"
#include "word_search_creator.h"
#include <math.h>
#include <assert.h>


int main(int  argc, char ** argv){
	int iflag = 0; //Flag nombre de archivo de entrada
	int hflag = 0; //Flag numero de hebras
	int cflag = 0; //Flag cantidad de palabras a ingresar
	int nflag = 0; //Flag ancho matriz
	int mflag = 0; //Flag largo matriz
	int sflag = 0; //Flag nombre de archivo de salida
	int dflag = 0; //Flag mostrar resultados por pantalla
	char * input_file = NULL;
	int threads_number = 0;
	int matrix_row = 0; // N
	int matrix_col = 0; // M
	int words_number = 0;
	char * output_file = NULL;
	int c;
	opterr=0;
	while((c = getopt(argc,argv,"i:h:c:n:m:s:d")) != -1){
		switch(c){
			case 'i':
				iflag = 1;
				input_file = malloc(strlen(optarg)+1);
				strcpy(input_file,optarg);
				break;
			case 's':
				sflag = 1;
				output_file = malloc(strlen(optarg)+1);
				strcpy(output_file,optarg);
				break;
			case 'h':
				hflag = 1;
				sscanf(optarg, "%d", &threads_number);
				break;
			case 'c':
				cflag = 1;
				sscanf(optarg, "%d", &words_number);
				break;
			case 'n':
				nflag = 1;
				sscanf(optarg, "%d", &matrix_row);
				break;
			case 'm':
				mflag = 1;
				sscanf(optarg, "%d", &matrix_col);
				break;
			case 'd':
				dflag = 1;
				break;
			case '?':
				if((optopt == 'i') || (optopt == 'h') || (optopt == 'c') || (optopt == 'n') || (optopt == 'm') || (optopt == 's')){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}else if(isprint(optopt)){
					fprintf(stderr, "Opcion desconocida '-%c'.\n", optopt);
				}else{
					fprintf(stderr, "Opcion con caracter desconocido '\\x%x'.\n", optopt);
				}
				return 1;
			default:
				abort();
		}
	}
	//En caso de que falten argumentos en la linea de comando
	if(argc < 13){
		printf("Faltan parametros para ingresar\n");
		return 1;
	}

	/*
	printf("iflag = %d, hflag = %d, cflag = %d, nflag = %d, mflag = %d, sflag = %d dflag = %d\n", iflag, hflag, cflag, nflag, mflag, sflag, dflag);
	printf("Archivo de entrada: %s\nNumero de hebras a crear: %d\nCantidad de palabras a ingresar: %d\nNumero de filas en matriz (N): %d\nNumero de columnas en matriz (M): %d\nArchivo de salida: %s\nImprime por pantalla: %s\n", 
		input_file,
		threads_number,
		words_number,
		matrix_col,
		matrix_row,
		output_file,
		dflag ? "Si":"No"
		);
	*/
	/*
		Procesamiento
	*/
	

	int i, j;
	FILE* in_file = fopen(input_file, "r");
	if(in_file == NULL) {
		printf("El archivo %s no existe, ejecute el programa con un archivo existente\n", input_file);
		return 1;
	}

	// Comprobando que la cantidad de palabras en el archivo concuerde con la cantidad de palabras que el usuario desea en la sopa
	if( count_input_words(in_file) < words_number ){
		printf("La cantidad de palabras a ingresar es mayor a la cantidad de palabras contenidas en el archivo\n");
		return 1;
	}

	// Reserva de memoria para matrix
	char ** matrix = allocate_matrix_memory(&matrix_row, &matrix_col);
	// Rellenado de matriz con caracteres especiales @
	matrix = initialize_matrix(matrix, &matrix_row, &matrix_col);

	// Inicializar matriz de posiciones
	init_positionable(matrix_row, matrix_col);


	// Se usa para tratar casos bordes en donde una hebra intenta usar mas palabras de las que quedan
	int words_left = words_number;
	int threads_left = threads_number;
	// Determina la cantidad de palabras que ingresará cada hebra
	int words_per_thread = (int)ceil((float) words_number / threads_number);

	if(threads_number > words_number){
		threads_number = words_number;
	}

	// Crear mutexes de acuerdo a la cantidad de filas en el archivo
	pthread_mutex_t* mutexes = malloc(matrix_row * sizeof(*mutexes));
	for (i = 0; i < matrix_row; ++i)
	{
		pthread_mutex_init(&(mutexes[i]), NULL);
	}

	// Arreglo de estrucuras de hebras
	WSThread * threads = malloc(threads_number*sizeof(WSThread));
	i = 0;
	while(i < threads_number){
		// Tener en cuenta que la division aproximada puede causar problemas.
		// Por lo que se revisa que no se intente sacar mas palabras de las que hay.
		words_per_thread = (int)ceil((float) words_left / threads_left);
		if(words_left - words_per_thread < 0) {
			words_per_thread = words_left;
		}

		WSThread_init(&(threads[i]), i+1, matrix_row, matrix_col, words_per_thread, mutexes, matrix, dflag);
		for (j = 0; j < words_per_thread; ++j)
		{
			WSThread_add_word(&(threads[i]), next_word(in_file), j);
		}

		pthread_create( &(threads[i].thread), NULL, locate, (void *) &(threads[i]));
		words_left -= words_per_thread;
		threads_left--;
		i++;
	}
	assert(words_left == 0);

	// Reunir hebras
	i = 0;
	while(i<threads_number){
		pthread_join( threads[i].thread, NULL);
		i++;
	}

	char*** matrixPointer = threads[0].matrix;
	// Rellenar la matriz con caracteres aleatorios donde tenga el caracter especial @
	fill_matrix(matrixPointer, matrix_row, matrix_col);


	if(dflag == 1){
		// Mostrar matriz
		show_matrix(matrix, &matrix_row, &matrix_col);
	}

	// Escribir el output en el archivo de salida
	FILE* out_file = fopen(output_file, "w");
	if(out_file == NULL) {
		printf("No se pudo crear el archivo %s, revise sus permisos e intente otra vez.\n", output_file);
		return 1;
	}

	for (int i = 0; i < matrix_row; ++i)
	{
		for (int j = 0; j < matrix_col; ++j)
		{
			fprintf(out_file, "%c", matrix[i][j]);
		}
		fprintf(out_file, "\n");
	}

	// Liberar memoria utilizada
	for (i = 0; i < matrix_row; ++i){
		free(matrix[i]);
	}
	free(matrix);

	fclose(in_file);
	fclose(out_file);
	free(mutexes);
	free(input_file);
	free(output_file);
	for (i = 0; i < threads_number; ++i){
		WSThread_free(&(threads[i]));
	}
	free(threads);
	free(matrix);

	/*
	// Comprobar que el largo de la cadena a buscar es menor o igual al largo
	// de cada linea
	if(strlen(cadena_a_buscar) > cantidad_caracteres_en_linea) {
		printf("El largo de la cadena que se quiere buscar es mayor a la cantidad de caracteres que hay en cada linea, por favor pruebe con otra cadena\n");
		return 1;
	}
		Procesamiento
	int caracteres_reales_en_linea = calcularCaracteresRealesEnLinea(archivo);
	if (caracteres_reales_en_linea != cantidad_caracteres_en_linea){
		printf("La cantidad de caracteres por línea a leer es distinta número real de caracteres que contiene el archivo de entrada \"%s\"\n",input_file);
		return 1;
	}
	char ch; int i;
	pid_t* procesos_hijos;
	int lineas_totales, lineas_por_proceso, lineas_restantes, posicion_cursor = 0;
	lineas_totales = calcularLineas(archivo, cantidad_caracteres_en_linea);
	lineas_por_proceso = (int)ceil((float)lineas_totales / numero_procesos_comparador);
	lineas_restantes = lineas_totales;
	procesos_hijos = (pid_t*)calloc(numero_procesos_comparador, sizeof(int));

	for (int i = 0; i < numero_procesos_comparador; ++i)
	{
		int lineas_proceso = lineas_por_proceso;
		if(lineas_restantes - lineas_proceso < 0) {
			lineas_proceso = lineas_restantes;
		}

		procesos_hijos[i] = createProcess(i+1, input_file, posicion_cursor, lineas_proceso, cadena_a_buscar);

		lineas_restantes -= lineas_proceso;
		if(lineas_restantes == 0) {
			break;
		}

		// Obtener la siguiente posicion del cursor en el archivo.
		int lineas_aux = 0;
		while((ch = (char)getc(archivo)) != EOF) {
			if(ch == '\n') {
				lineas_aux++;
			}
			if(lineas_aux == lineas_proceso) {
				break;
			}
		}
		posicion_cursor = ftell(archivo);
	}

	*/
	/*
		Escribir resultados en un archivo.

	// Esperar que terminen todos los procesos creados.
	for (int i = 0; i < numero_procesos_comparador; ++i)
	{
		waitpid(procesos_hijos[i], NULL, 0);
	}

	int caracteres_por_proceso = (lineas_por_proceso) * (cantidad_caracteres_en_linea + 3 + 1);
	char* buffer = (char*)malloc(caracteres_por_proceso + 1);
	char* nombre_archivo_completo = getRcName(cadena_a_buscar);
	FILE* resultados_completos = fopen(nombre_archivo_completo, "w");
	for (int i = 1; i <= numero_procesos_comparador; ++i)
	{
		char* nombre_archivo_parcial = getRpName(cadena_a_buscar, i);
		FILE* resultado_parcial = fopen(nombre_archivo_parcial, "r");
		if(resultado_parcial == NULL) {
			continue;
		}

		fread(buffer, caracteres_por_proceso + 1, 1, resultado_parcial);
		fwrite(buffer, strlen(buffer), 1, resultados_completos);
		if(dflag == 1) {
			printf("%s", buffer);
		}

		fclose(resultado_parcial);
		free(nombre_archivo_parcial);
	}
	free(buffer);
	fclose(resultados_completos);
	free(nombre_archivo_completo);
	
	free(procesos_hijos);
	free(cadena_a_buscar);
	*/
	return 0;
}

