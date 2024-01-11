# Prácticas de Lenguaje C en GNU/Linux

Este repositorio tiene como objetivo repasar conceptos básicos del lenguaje C, incluyendo el manejo de C-strings, arreglos, y estructuras. Se realizaron diversas actividades, las cuales se describen a continuación.

### Autores:
- **Bottini, Franco Nicolas**

### 1. C-strings

**Obtención de información sobre la memoria RAM**

Se implementó un programa en C que lee el archivo `/proc/meminfo` para obtener información sobre la memoria RAM total, libre y disponible en megabytes. Además, se obtiene la memoria swap ocupada.

**Impresión de información sobre el CPU**

Se creó un programa en C que imprime información sobre el CPU, utilizando el archivo `/proc/cpuinfo`. La información incluye el modelo de CPU, la cantidad de cores y la cantidad de threads por core.

### 2. Arreglos

**Lectura y manipulación de archivo `/proc/version`**

Se implementó un programa en C que lee el archivo `/proc/version`, copia las palabras en un arreglo dinámico y luego imprime la lista de palabras en mayúsculas. Se liberó la memoria asignada.

### 3. Respuestas a las preguntas

#### ¿Cómo utilizar typedef junto a struct? ¿Para qué sirve? Ejemplo.

typedef se utiliza para asignar un nombre alternativo a tipos existentes, a menudo cuando su declaración normal es aparatosa, potencialmente confusa o probablemente variable de una implementación a otra. Generalmente se utiliza en las estructuras para simplificar la declaracion de las mismas, esto resulta en un código mucho más limpio y evita la aparicion de la palabra clave <i>"struct"</i> por todas partes. Un ejemplo de utilizacion de esto seria:
       
```C
   typedef struct Persona { 
      char Nombre[50];
       uint8_t Edad;
       uint32_t DNI; 
   } Persona; 
```
       
#### ¿Qué es packing and padding?

El concepto de padding hace referencia a alinear los datos en memoria, para ello, se insertan uno o más bytes de "relleno" entre las direcciones de memoria asignadas a los miembros de la estructura. La ventaja de hacer esto, radica en que el procesador no lee la memoria byte a byte sino que lo hace por palabras (bloques de memoria con longitud mayor a 1 byte), por lo tanto al alinear los datos para formar palabras de tamaño fijo, se vuelve mas eficiente la lectura de la memoria. La desventaja de esto, es que se opcupa una mayor cantidad de memoria para almacenar las estructuras. Por otro lado, podemos aplicar packing para evitar que el compilador por si mismo realice padding (está habilidato por defecto). Esto generalmente se utiliza para ahorrar memoria y formatear una estructura de datos para transmitir a través de una red sin depender de la arquitectura de cada uno de los nodos. Las desventajas de hacer esto es que perdemos eficiencia en el procesamiento, y ademas, no todos los procesadores son capaces de realizar packing.

#### Explique a que se debe los tamaños de cada una de las estructuras.

```C
   printf("base     struct size  %lu \n", sizeof(BaseData));
   printf("reorder  struct size  %lu \n", sizeof(ReorderData));
   printf("extended struct size  %lu \n", sizeof(ExtendedData));
   printf("packed   struct size  %lu \n\n", sizeof(BaseDataPacked));
```

El espacio en memoria que ocupa una estructura depende de la suma del tamaño de los tipos de datos que la conforman y del padding realizado por la CPU, por ejemplo, si tenemos una estructura compuesta por un char (1 byte) y un int (4 bytes) la estructura necesita como mínimo (en caso de utilizarse packing) un espacio de 5 bytes en memoria. Analizando cada uno de los casos del programa: <br>

- <b>BaseData</b>: En este caso se ocupan los primeros 2 bytes con ```char a``` y ```char b```, luego el compilador rellena con un espacio de 2 bytes, sigue con ```int x``` el cual ocupa 4 bytes, ```unsigned short int y``` y ```char c``` más otro byte de relleno para completar los 4 bytes, finalmente ```unsigned short int z``` más un relleno de 2 bytes y finalmente ```char d[3]``` más otro byte de relleno.

```C
   typedef struct {
      char a;
      char b;
      char gap_0[2]; /* Insertado por el compilador para alinear x. */
      int  x;
      unsigned short int y;
      char c;
      char gap_1; /* Insertado por el compilador para alinear z. */
      unsigned short int z;
      char gap_2[2]; /* Insertado por el compilador para alinear d. */
      char d[3];
      char gap_3; /* Insertado por el compilador para alinear toda la estructura en una matriz. */
   } BaseData; 
      
   /* sizeof(BaseData) = 
         sizeof(char) * 5               +
         sizeof(char[2]) * 2            +
         sizeof(char[3])                +
         sizeof(int)                    +
         sizeof(unsigned short int) * 2 +
      ------------------------------------
                               20 [Bytes]
   */
```

- <b>ReorderData</b>: Igual que en el caso anterior, ```char a``` y ```char b``` ocupan los 2 primeros bytes, se rellenan los siguientes 2 y se ocupan 4 para el ```int x```. Luego los ```unsigned short int y, z``` se colocan ocupando 2 bytes cada uno. Ahora gracias a este orden ```char c``` y ```char d[3]``` estan alineados ocupando 1 y 3 bytes contiguos respectivamente.

```C
   typedef struct {
      char a;
      char b;
      char gap_0[2]; //Insertado por el compilador para alinear x.
      int  x;
      unsigned short int y;
      unsigned short int z;
      char c;
      char d[3];
   } ReorderData;
    
   /* sizeof(BaseData) = 
         sizeof(char) * 3               +
         sizeof(char[2])                +
         sizeof(char[3])                +
         sizeof(int)                    +
         sizeof(unsigned short int) * 2 +
      ------------------------------------
                               16 [Bytes]
   */
```

- <b>ExtendedData</b>: En este caso se ocupan los primeros 8 bytes con ```long unsigned int ll```, ```char a``` y ```char b```, luego, con ```unsigned short int y``` y rellenando 2 espacios para completar los 4 bytes, sigue con ```int x``` el cual ocupa 4 bytes, ```unsigned short int z```, ```unsigned short int w``` completando los 4 bytes, finalmente ```char c```, ```char d[3]```, que logran 4 bytes.

```C
   typedef struct {
      long unsigned int ll;
      char a;
      char b;
      unsigned short int y;
      int  x;
      unsigned short int z;
      unsigned short int w;
      char c;
      char d[3];
   } ExtendedData;
      
   /* sizeof(BaseData) = 
         sizeof(char) * 3               +
         sizeof(char[3])                +
         sizeof(int)                    +
         sizeof(unsigned short int) * 3 +
         sizeof(long unsigned int)      +
      ------------------------------------
                               24 [Bytes]
   */
```

- <b>BaseDataPacked</b>: En este caso utilizamos la caracacteristica de packing, en la cual el compilador no rellena bytes para completar bloques de 4. Esto produce que el procesador no pueda leer toda la memoria en un solo acceso, sino que, en la mayoria de los casos, debera ocupar multiples ciclos de lectura para obtener la información, haciendo mas lento el procesamiento.

```C
   typedef struct  __attribute__((packed)) {
      char a;
      char b;
      int  x;
      unsigned short int y;
      char c;
      unsigned short int z;
      char d[3];
   } BaseDataPacked;
      
   /* sizeof(BaseData) = 
         sizeof(char) * 3               +
         sizeof(char[3])                +
         sizeof(int)                    +
         sizeof(unsigned short int) * 2 +
      ------------------------------------
                               14 [Bytes]
   */
```

#### Explique por que las expresiones que calculan ```limit``` y ```limit_aux``` generan el mismo resutado.

```C   
   char *limit = ((char *) &data + sizeof(BaseData)); 
   char *limit_aux =(char *) (&data + 1);

   printf("limit     value is %p \n", limit); 
   printf("limit_aux value is %p \n\n", limit_aux);
```

En el primer caso, debemos partir del hecho de que estamos casteando una estructura, la cual originalmente ocupa 20 bytes en la memoria, al castearlo a un puntero tipo ```char*``` ahora este va a apuntar a un solo byte. Luego se le suma el sizeof(BaseData), por aritmetica de punteros ```p* + n``` quiere decir que se va a desplazar el puntero ```n``` elementos del tipo del mismo, como en este caso es un char, se va a desplazar byte a byte, 20 veces. Por otra parte, En el segundo caso vemos que la suma se realiza antes que el casteo, esto es muy importante, ya que ahora se va a desplazar al elemento siguiente pero de la estructura original, la cual ocupa 20 bytes. Por ende, en ambos casos terminamos en la misma dirección de memoria.

#### Explique los valores que se muestran en pantalla en cada iteracion del ```for```.

```C
    int i = 0;

    for (char *c = (char *) &data; c < limit; c++, i++){
        printf("byte %02d : 0x%02hhx \n", i, *c);
    }
```

El ```for``` recorre byte por byte las posiciones de memoria donde se aloja la estructura ```data``` imprimendo el valor que almacena cada uno de estos por consola.
