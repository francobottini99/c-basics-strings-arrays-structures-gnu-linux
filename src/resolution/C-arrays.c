/**
 * @file C-arrays.c
 * @author 
 *  - Bottini, Franco Nicolas
 *  - Lavezzari, Fausto
 *  - Robledo, Valentin
 *  - Lencina, Aquiles Benjamin
 * @brief Resolución del ejercicio de arrays del laboratorio 2, Sistemas Operativos I.
 * @version 1.1
 * @date Agosto de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "C-arrays.h"

/**
 * @brief Obtiene todas las palabras de un archivo dado.
 * 
 * Genera un array bidimensional dinamico con todas las palabras contenidas en el archivo 
 * especificado. Minimiza la memoria empleada para el almacenamiento de dichas palabras.
 * 
 * @param file_name archivo sobre del cual se quieren obtener las palabras.
 * @param n puntero donde se va a almacenar el numero de palabras obtenidas.
 * @return char** direccion de memoria del array bidimensional donde se encuentran las palabras obtenidas.
 */
char** getWords(char* file_name, u_int32_t* n)
{
    u_int32_t w_count = 0;
    u_int32_t c_count = 0;

    char last = ' ';
    char c;

  	FILE* file;

    char** words = malloc(sizeof(char*)); // En primera instancia se reserva memoria para alamacenar una palabra
    words[w_count] = malloc(sizeof(char)); // Se reserva memoria para al menos un caracter en la primera palabra

	file = fopen(file_name, "r");
    
  	if(file == NULL) 
		exit(EXIT_FAILURE);

    while ((c = (char)fgetc(file)) != EOF) // Se recorre todo el documento caracter por caracter
    {
        if(c == ' ' && last != ' ')  // Verifica si el digito actual es un espacio y el anterior no
        {
            words[w_count][c_count] = '\0'; // En caso de ser asi termina la palabra con el caracter de finalizacion

            w_count++;
            c_count = 0;

            words = realloc(words, (w_count + 1) * sizeof(char*)); // Se redimenciona la memoria reservada para almacenar una nueva palabra
            words[w_count] = malloc(sizeof(char)); // Se reserva espacio para el primer caracter de la nueva palabra
        } 
        else
        {
            if(c != '(' && c != ')') // Ignoramos los parentesis
            {
                words[w_count][c_count] = c; // Agrega el caracter a la palabra actual
                c_count++;
                words[w_count] = realloc(words[w_count], (c_count + 1) * sizeof(char)); // Se redimenciona la memoria reservada para la plabra actual para almacenar el siguiente caracter
            }
        }

        last = c;
    }

    words[w_count][c_count] = '\0'; // Finalizamos la ultima palabra con el caracter correspondiente

    *n = w_count; // Guardamos el numero de palabras obtenidas

  	fclose(file);

    return words;
}

/**
 * @brief Libera el espacio de memoria donde se almacenan las palabras.
 * 
 * @param words direccion de memoria donde se encuenta el array bidimensional de palabras.
 * @param n numero de palabras almacenadas en el array.
 */
void freeWords(char** words, u_int32_t n)
{
    for(int i = 0; i < n; i++) // Recorre todas las palabras del array
    {
        free(words[i]);
    }

    free(words);
}

/**
 * @brief Imprime por consola las palabras de un array en mayusculas. 
 * 
 * @param words direccion de memoria donde se encuenta el array bidimensional de palabras.
 * @param n numero de palabras almacenadas en el array.
 */
void upperCasePrintWords(char** words, u_int32_t n) 
{
    printf("- UPPER CASE WORDS (/proc/version):\n");
    
    for(int i = 0; i < n; i++)
    {
        printf("    ");

        for(int j = 0; words[i][j] != '\0'; j++) { // Recorre todos los caracteres dentro de una palabra
            if(words[i][j] >= 97 && words[i][j] <= 122) // Verifica que el caracter se corresponda con una letra miniscula de acuerdo a la codificacion ASCII
                printf("%c", words[i][j] - 32); // Se transforma la letra a mayusculas (la distancia entre una letra minuscula y su contraparte mayuscula es de -32 en la codificacion ASCII,) y se imprime en consola
            else 
                printf("%c", words[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}