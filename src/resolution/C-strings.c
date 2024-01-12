/**
 * @file C-strings.c
 * @author
 *  - Bottini, Franco Nicolas
 *  - Lavezzari, Fausto
 *  - Robledo, Valentin
 *  - Lencina, Aquiles Benjamin
 * @brief Resolución del ejercicio de strings del laboratorio 2, Sistemas Operativos I.
 * @version 1.1
 * @date Agosto de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "C-strings.h"

/**
 * @brief Imprime en consola información acerca de la memoria.
 * 
 */
void printMemoryInfo(void)
{
    MEM_INFO memInfo;

    getMemInfo(&memInfo);

	printf("- MEM INFO (/proc/meminfo):\n");
    printf("	Memoria Total      : %*lu [MB]\n", 7, memInfo.MemTotal     / 1024);
    printf("	Memoria Libre      : %*lu [MB]\n", 7, memInfo.MemFree 	   / 1024);
    printf("	Memoria Disponible : %*lu [MB]\n", 7, memInfo.MemAvailable / 1024);
    printf("	Swap Total         : %*lu [MB]\n", 7, memInfo.SwapTotal    / 1024);
    printf("	Swap Libre         : %*lu [MB]\n\n", 7, memInfo.SwapFree     / 1024);
}

/**
 * @brief Imprime en consola información acerca del CPU.
 * 
 */
void printCpuInfo(void)
{
    CPU_INFO cpuInfo;

    getCpuInfo(&cpuInfo);

	printf("- CPU INFO (/proc/cpuinfo):\n");
    printf("	Modelo             : %s\n", cpuInfo.ModelName);
    printf("	Nucleos            : %d\n", cpuInfo.Cores);
    printf("	Hilos              : %d\n\n", cpuInfo.Threads);
}

/**
 * @brief Obtiene informacion acerca de la memoria.
 * 
 * Realiza la lectura y procesamiento de la informacion almacenada en el archivo "/proc/meminfo" 
 * para posteriormente almacenarla en el puntero a la estructura dada como parametro.
 * 
 * @param memInfo puntero a la estructura donde se quiere almacenar la informacion obtenida.
 */
void getMemInfo(MEM_INFO* memInfo)
{
	char* line = NULL;
	ssize_t read;
	size_t len;
  	FILE *file;

	file = fopen("/proc/meminfo", "r");
  
  	if(file == NULL) 
		exit(EXIT_FAILURE); // Si ocurrio un error al intentar abrir el archivo finaliza la ejecucion del programa

	while ((read = getline(&line, &len, file)) != -1) // Recorre linea por linea el archivo
	{
		char* token = strtok(line, ":"); // Divide la linea en dos por medio del simbolo ":"
		
		// Compara la primer subcadena obtenida en busca de la informacion deseada
		if (strncmp(token, "MemTotal", 8) == 0) {
			token = strtok(NULL, ":"); // Selecciona la segunda subcadena, la cual contiene el dato de interes
			memInfo->MemTotal = atol(strtok(token, " ")); // Almacena el dato en la locacion correspondiente
		}

		if (strncmp(token, "MemFree", 7) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->MemFree = atol(strtok(token, " "));
		}

		if (strncmp(token, "MemAvailable", 12) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->MemAvailable = atol(strtok(token, " "));
		}

		if (strncmp(token, "SwapTotal", 9) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->SwapTotal = atol(strtok(token, " "));
		}

		if (strncmp(token, "SwapFree", 8) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->SwapFree = atol(strtok(token, " "));
		}
	}

  	fclose(file);

	if (line)
        free(line);
}

/**
 * @brief Obtiene informacion acerca de la CPU.
 * 
 * Realiza la lectura y procesamiento de la informacion almacenada en el archivo "/proc/cpuinfo" 
 * para posteriormente almacenarla en el puntero a la estructura dada como parametro.
 * 
 * @param cpuInfo puntero a la estructura donde se quiere almacenar la informacion obtenida.
 */
void getCpuInfo(CPU_INFO* cpuInfo)
{
	char* line = NULL;
	ssize_t read;
	size_t len;
  	FILE *file;

	file = fopen("/proc/cpuinfo", "r");
  
  	if(file == NULL) 
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, file)) != -1)
	{
		char* token = strtok(line, ":");
		
		if (strncmp(token, "model name", 10) == 0) {	
			/* Este bloque de codigo se encarga de eliminar los espacios en blanco al principio
			 y al final de la cadena que contiene la informacion del modelo del CPU */	

  			const char *end;
  			token = strtok(NULL, ":"); 

    		while(isspace((unsigned char)*token)) token++;

	 		end = token + strlen(token) - 1;
  			while(end > token && isspace((unsigned char)*end)) end--;
  			end++;

  			memcpy(cpuInfo->ModelName, token, (end - token));
  			cpuInfo->ModelName[(end - token)] = 0;
		}

		if (strncmp(token, "cpu cores", 9) == 0)  
		{
			token = strtok(NULL, ":"); 
			cpuInfo->Cores = atoi(strtok(token, " "));
		}

		if (strncmp(token, "siblings", 8) == 0)  
		{
			token = strtok(NULL, ":"); 
			cpuInfo->Threads = atoi(strtok(token, " "));
		}
	}

  	fclose(file);

	if (line)
        free(line);
}