#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))
#define MARKER_LENGTH 4

typedef struct CHAR_MEMORY{
    unsigned int next_index;
    unsigned int max_storage;
    char chars[];
} CHAR_MEMORY;

void pushCharToMemory(CHAR_MEMORY* mem, char c){
    mem->chars[mem->next_index] = c;
    mem->next_index = (mem->next_index + 1) % mem->max_storage;
}

bool checkMemoryForMarek(CHAR_MEMORY* mem){
    unsigned long bitmap = 0;
    for(unsigned int i = 0; i<mem->max_storage; i++){
        unsigned int index = mem->chars[i] - 'a';
        if(bitmap & (1UL << index)){
            return false;
        }
        bitmap |= (1UL << index);
    }
    return true;
}


int main(){
    char buffer[BUFFER_SIZE] = {0};
    char *p = NULL;
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }

    CHAR_MEMORY* last4chars = malloc(sizeof(*last4chars) + (sizeof(char) * MARKER_LENGTH));
    last4chars->next_index = 0;
    last4chars->max_storage = MARKER_LENGTH;
    unsigned int startOfPacketPosition = 0;

    char c = getc(input_fp);
    while (c != EOF) 
    {
        startOfPacketPosition++;
        pushCharToMemory(last4chars,c);
        if(startOfPacketPosition>MARKER_LENGTH && checkMemoryForMarek(last4chars)){
            break;
        }
        c = getc(input_fp);
    }   
    printf("%u\n",startOfPacketPosition);
}