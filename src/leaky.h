#ifndef LEAKY_H
#define LEAKY_H

#ifdef __cpluscplus
extern "C"
{
#endif // __cpluscplus

#define ALLOCATION_SIZE_MAX 1024

typedef unsigned int uint_t;

static uint_t initialized = 0;

typedef struct {
    void* allocationAddress;
    uint_t allocationSize;

    uint_t allocationLine;
    char allocationFile[255];
} memory;

static struct {
    memory allocationData[ALLOCATION_SIZE_MAX];

    uint_t allocationsTotalSize;
    uint_t freeTotalSize;

    uint_t allocationsCallsTotal;
    uint_t freeCallsTotal;

    uint_t current;
} memoryData;

static void leakyInit();
static int leakyAllocate(void* data, uint_t line, char* file, uint_t size);
static int leakyDeallocate(void* data);

void* leakyMalloc(uint_t line, char* file, int Size);
void* leakyCalloc(uint_t line, char* file, int NumOfElements, int SizeOfElements);
// void* leakyRealloc(uint_t line, char* file, void* Memory, int NewSize);
void leakyFree(void* Memory);

void leakyRaport();

#ifdef LEAKY_IMPLEMENTATION

#include <corecrt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static void leakyInit(){
    if(initialized == 0) {
        initialized = 1;
        
        // at the end of the program print the general and detailed raport
        atexit(leakyRaport);
    }
}

static int leakyAllocate(void* data, uint_t line, char* file, uint_t size){
    if(!data){
        perror("[ERR]");
        return -1;
    }

    if(memoryData.current < ALLOCATION_SIZE_MAX) {
        memoryData.allocationData[memoryData.current].allocationAddress = data;
        memoryData.allocationData[memoryData.current].allocationSize = size;
        memoryData.allocationData[memoryData.current].allocationLine = line;
        
        strcpy(memoryData.allocationData[memoryData.current].allocationFile, file);

        memoryData.current++;
        memoryData.allocationsCallsTotal++;
        memoryData.allocationsTotalSize += size;

        return 0;
    }

    return -1;
}

static int leakyDeallocate(void *data){
    if(!data) {
        perror("[ERR]");
        return -1;
    }

    for(int i = 0; i < ALLOCATION_SIZE_MAX; i++) {
        if(data == memoryData.allocationData[i].allocationAddress){
            memoryData.allocationData[i].allocationAddress = NULL;
            
            memoryData.freeCallsTotal++;
            memoryData.freeTotalSize += memoryData.allocationData[i].allocationSize;

            return 0;
        }
    }

    return -1;
}

void* leakyMalloc(uint_t line, char* file, int Size){
    if(initialized == 0){
        leakyInit();
    }

    void* data = malloc(Size);
    if(!data) {
        perror("[ERR]");
        return NULL;
    }
    
    leakyAllocate(data, line, file, Size);

    return data;
}

void* leakyCalloc(uint_t line, char* file, int NumOfElements, int SizeOfElements) {
    if(initialized == 0){
        leakyInit();
    }

    void* data = calloc(NumOfElements, SizeOfElements);
    if(!data) {
        perror("[ERR]");
        return NULL;
    }

    leakyAllocate(data, line, file, NumOfElements * SizeOfElements);

    return data;
}

/* TODO: fix this

void* leakyRealloc(uint_t line, char* file, void* Memory, int NewSize) {
    if(initialized == 0){
        leakyInit();
    }

    void* newData = realloc(Memory, NewSize);
    if(!newData) {
        perror("[ERR]");
        return NULL;
    }

    leakyFree(Memory);
    leakyAllocate(newData, line, file, NewSize);

    return newData;
}

*/

void leakyFree(void* Memory){
    if(initialized == 0){
        leakyInit();
    }

    if(!Memory){
        return;
    }

    leakyDeallocate(Memory);
    free(Memory);
}

void leakyRaport(){
    printf("+----------------------------------+\n");
    printf("|       LEAKY GENERAL RAPORT       |\n");
    printf("+----------------------------------+\n");
    printf("> Total 'allocation' calls: %i calls\n", memoryData.allocationsCallsTotal);
    printf("> Total 'free' calls:       %i calls\n", memoryData.freeCallsTotal);
    printf("> Memory allocated:         %i bytes\n", memoryData.allocationsTotalSize);
    printf("> Memory freed:             %i bytes\n", memoryData.freeTotalSize);
    printf("+----------------------------------+\n\n");

    if(memoryData.allocationsCallsTotal == memoryData.freeCallsTotal) {
        return;
    }

    printf("+-----------------------------------+\n");
    printf("|       LEAKY DETAILED RAPORT       |\n");
    printf("+-----------------------------------+\n");

    for(int i = 0; i < ALLOCATION_SIZE_MAX; i++) {
        if(memoryData.allocationData[i].allocationAddress != NULL) {
            printf("> Memory leak at: %s:%i (size: %i bytes)\n", memoryData.allocationData[i].allocationFile, memoryData.allocationData[i].allocationLine, memoryData.allocationData[i].allocationSize);
        }
    }

    printf("+-----------------------------------+\n\n");

}

#define malloc(Size) leakyMalloc(__LINE__, __FILE__, Size) 
#define calloc(NumOfElements, SizeOfElements) leakyCalloc(__LINE__, __FILE__, SizeOfElements, NumOfElements)
// define realloc(Memory, NewSize) leakyRealloc(__LINE__, __FILE__, Memory, NewSize) TODO: implement the 'realloc' so that it won't cause any segmentation problems
#define free(Memory) leakyFree(Memory) 

#endif // LEAKY_IMPLEMENTATION

#ifdef __cpluscplus
}
#endif // __cpluscplus

#endif // LEAKY_H