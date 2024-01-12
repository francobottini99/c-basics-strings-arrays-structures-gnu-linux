/**
 * @file C-structs.h
 * @author
 *  - Bottini, Franco Nicolas
 *  - Lavezzari, Fausto
 *  - Robledo, Valentin
 *  - Lencina, Aquiles Benjamin
 * @brief Encabezado del archivo C-structs.c
 * @version 1.1
 * @date Agosto de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CSTRUCTS_H__
#define __CSTRUCTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE
{
	int value;
	struct NODE *next;
} NODE;

typedef NODE* List;

void append(List* list, int value);
void printList(List list);

#endif //__CSTRUCTS_H__