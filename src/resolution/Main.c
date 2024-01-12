/**
 * @file Main.c
 * @author
 *  - Bottini, Franco Nicolas
 *  - Lavezzari, Fausto
 *  - Robledo, Valentin
 *  - Lencina, Aquiles Benjamin
 * @brief Se implementa la resolucion de todos los ejercicios del laboratiorio 2, Sistemas Operativos I.
 * 
 * Para compilar y poder ejecutar el programa se deben compilar de manera conjunta los archivos:
 *  - Main.c
 *  - C-arrays.c
 *  - C-strings.c
 *  - C-structs.c
 * 
 * Se puede realizar esta tarea utilizando el comando:
 *  $ gcc Main.c C-arrays.c C-strings.c C-structs.c -o <nombre del archivo de salida> -Wall -Werror -pedantic 
 * 
 * @version 1.1
 * @date Agosto de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "C-arrays.h"
#include "C-strings.h"
#include "C-structs.h"

int main(void)
{  
    u_int32_t n;
    List rand_list = NULL; // Creamos una lista vacia
    char** words = getWords("/proc/version", &n); // Obtenemos las palabras del archivo dado

    srand(time(NULL));
    for(int i = 0; i < 20; i++) // Rellenamos la lista con elementos aleatorios
    {
        append(&rand_list, rand());
    } 

    printCpuInfo(); // Mostramos por consola la informacion del CPU
    printMemoryInfo(); // Mostramos por consola la informacion de la memoria

    upperCasePrintWords(words, n); // Mostramos por consola las palabras obtenidas en mayuscula

    printList(rand_list); // Mostramos por consola todos los elementos de la lista generada

    freeWords(words, n); // Liberamos la memoria utilizada para almacenar las palabras

    return 0;
}