# C Language Practices in GNU/Linux

This repository provides a review of basic C language concepts, including handling C-strings, arrays, and structures. Various activities were completed, as described below.

### Author:
- **Franco Nicolas Bottini**

### 1. C-strings

**Retrieving RAM Information**

A C program was implemented to read the `/proc/meminfo` file and extract information about the total, free, and available RAM in megabytes. Additionally, the occupied swap memory is obtained.

**Displaying CPU Information**

A C program was created to display information about the CPU by reading the `/proc/cpuinfo` file. The program provides details about the CPU model, core count, and threads per core.

### 2. Arrays

**Reading and Manipulating `/proc/version` File**

A C program was implemented to read the `/proc/version` file, copy the words into a dynamic array, and then print the list of words in uppercase. The allocated memory is freed afterward.

### 3. Answers to Questions

#### How to use typedef with struct? What is it for? Example.

The `typedef` keyword is used to assign an alternative name to existing types, often when their declaration is cumbersome, potentially confusing, or likely variable between implementations. It is commonly used with structures to simplify their declaration, resulting in cleaner code and avoiding the frequent use of the `struct` keyword. Here’s an example:

```C
typedef struct Person { 
   char Name[50];
   uint8_t Age;
   uint32_t ID; 
} Person; 
```

#### What are packing and padding?

**Padding** refers to aligning data in memory by inserting one or more "filler" bytes between memory addresses assigned to the members of a structure. The advantage of this approach is that the processor reads memory in words (blocks of memory larger than one byte) rather than byte-by-byte. Aligning data into fixed-size words can make memory access more efficient. However, padding consumes more memory.

On the other hand, **packing** prevents the compiler from inserting padding bytes (which is enabled by default). Packing is generally used to save memory and format data structures for network transmission, independent of the architecture of each node. However, packing can reduce processing efficiency, and not all processors support packed structures.

#### Explain the sizes of each of the structures.

```C
printf("base struct size %lu \n", sizeof(BaseData));
printf("reorder struct size %lu \n", sizeof(ReorderData));
printf("extended struct size %lu \n", sizeof(ExtendedData));
printf("packed struct size %lu \n\n", sizeof(BaseDataPacked));
```

The memory size of a structure depends on the total size of its data types and the padding inserted by the CPU. For example, if we have a structure composed of a `char` (1 byte) and an `int` (4 bytes), the structure requires at least 5 bytes in memory (in the case of packing).

Analyzing each case:

- **BaseData**: In this case, `char a` and `char b` occupy the first 2 bytes, followed by 2 padding bytes. `int x` occupies 4 bytes, `unsigned short int y` and `char c` occupy 4 bytes together, with one filler byte to complete. `unsigned short int z` is padded with 2 bytes, and finally, `char d[3]` requires one extra filler byte.

```C
typedef struct {
   char a;
   char b;
   char gap_0[2]; // Inserted by the compiler for aligning x.
   int  x;
   unsigned short int y;
   char c;
   char gap_1; // Inserted by the compiler to align z.
   unsigned short int z;
   char gap_2[2]; // Inserted by the compiler for aligning d.
   char d[3];
   char gap_3; // Inserted by the compiler to align the entire structure within an array.
} BaseData; 

// sizeof(BaseData) = 
//       sizeof(char) * 5               +
//       sizeof(char[2]) * 2            +
//       sizeof(char[3])                +
//       sizeof(int)                    +
//       sizeof(unsigned short int) * 2 +
// ------------------------------------
//                          20 [Bytes]
```

- **ReorderData**: Similarly, `char a` and `char b` take the first 2 bytes, followed by 2 filler bytes. `int x` occupies 4 bytes, and `unsigned short int y, z` occupy 2 bytes each. `char c` and `char d[3]` are contiguous, using 1 and 3 bytes, respectively.

```C
typedef struct {
   char a;
   char b;
   char gap_0[2]; // Inserted by the compiler for aligning x.
   int  x;
   unsigned short int y;
   unsigned short int z;
   char c;
   char d[3];
} ReorderData;

// sizeof(ReorderData) = 
//       sizeof(char) * 3               +
//       sizeof(char[2])                +
//       sizeof(char[3])                +
//       sizeof(int)                    +
//       sizeof(unsigned short int) * 2 +
// ------------------------------------
//                          16 [Bytes]
```

- **ExtendedData**: This case occupies the first 8 bytes with `long unsigned int ll`, `char a`, and `char b`. `unsigned short int y` is followed by 2 filler bytes, `int x` uses 4 bytes, `unsigned short int z` and `unsigned short int w` complete 4 bytes, and `char c` and `char d[3]` use 4 bytes.

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

// sizeof(ExtendedData) = 
//       sizeof(char) * 3               +
//       sizeof(char[3])                +
//       sizeof(int)                    +
//       sizeof(unsigned short int) * 3 +
//       sizeof(long unsigned int)      +
// ------------------------------------
//                          24 [Bytes]
```

- **BaseDataPacked**: Using packing, the compiler does not add padding bytes to complete 4-byte blocks. This means the processor may need multiple read cycles to access memory, slowing down processing.

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

// sizeof(BaseDataPacked) = 
//       sizeof(char) * 3               +
//       sizeof(char[3])                +
//       sizeof(int)                    +
//       sizeof(unsigned short int) * 2 +
// ------------------------------------
//                          14 [Bytes]
```

#### Explain why the expressions that calculate `limit` and `limit_aux` generate the same result.

```C   
char *limit = ((char *) &data + sizeof(BaseData)); 
char *limit_aux = (char *) (&data + 1);

printf("limit     value is %p \n", limit); 
printf("limit_aux value is %p \n\n", limit_aux);
```

In the first case, the structure, originally occupying 20 bytes, is cast to a `char*` pointer, which points to a single byte. Adding `sizeof(BaseData)` moves the pointer 20 bytes (one byte at a time due to `char*` pointer arithmetic). 

In the second case, the addition occurs before the cast, so the pointer moves to the next structure, which occupies 20 bytes. Both end up at the same memory address.

#### Explain the values displayed for each iteration of the `for` loop.

```C
int i = 0;

for (char *c = (char *) &data; c < limit; c++, i++){
   printf("byte %02d : 0x%02hhx \n", i, *c);
}
```

The `for` loop iterates through each byte in the memory allocated to the `data` structure, printing the value stored in each byte.
