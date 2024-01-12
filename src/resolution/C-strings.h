/**
 * @file C-strings.h
 * @author
 *  - Bottini, Franco Nicolas
 *  - Lavezzari, Fausto
 *  - Robledo, Valentin
 *  - Lencina, Aquiles Benjamin
 * @brief Encabezado del archivo C-strings.c
 * @version 1.1
 * @date Agosto de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CSTRINGS_H__
#define __CSTRINGS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct MEM_INFO        
{      
    u_int64_t MemTotal;   
    u_int64_t MemFree;  
    u_int64_t MemAvailable;
    u_int64_t SwapTotal;
    u_int64_t SwapFree;
} MEM_INFO;

typedef struct CPU_INFO
{
    u_int32_t Cores;
    u_int32_t Threads;
    char ModelName[1024];
} CPU_INFO;

void getMemInfo(MEM_INFO* memInfo);
void getCpuInfo(CPU_INFO* cpuInfo);
void printMemoryInfo(void);
void printCpuInfo(void);

#endif //__CSTRINGS_H__