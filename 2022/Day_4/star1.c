#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

typedef struct RANGE {
    unsigned int left;
    unsigned int right;
} RANGE;

bool isRangeContained(RANGE range1, RANGE range2){
    return ((range1.left<=range2.left && range1.right>=range2.right) ||
            (range2.left<=range1.left && range2.right>=range1.right));
}

int main(){
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    char *p;
    unsigned totalPairsContained = 0;
    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        RANGE elf1;
        RANGE elf2;
        sscanf(buffer,"%d-%d,%d-%d", &elf1.left,&elf1.right,&elf2.left,&elf2.right);
        totalPairsContained += isRangeContained(elf1,elf2) ? 1 : 0;
    }
    printf("%u\n",totalPairsContained);
}