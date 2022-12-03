#include <stdio.h>
#include<stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)
#define BITSTOTAL 52

typedef struct bitMap {
    unsigned int chunks;
    char bits[];
} bitMap;

unsigned int charPositionInSet(char item){
    if (item >= 'A' && item <= 'Z'){
        return (item - 'A' + (BITSTOTAL/2));
    }
    else if (item >= 'a' && item <= 'z'){
        return (item - 'a');
    }
    printf("This char is out of range: %c\n",item);
    exit(EXIT_FAILURE);
}

void setItem(bitMap* set, char item){
    BITSET(set->bits,charPositionInSet(item));
}

bitMap* createSet(unsigned int noOfChunks){
    bitMap* set = NULL;
    set = (bitMap *) malloc(sizeof(*set)  + (sizeof(char) * noOfChunks));
    for(unsigned int i=0; i<noOfChunks; i++){
        set->bits[i] = 0;
    }
    set->chunks = noOfChunks;
    return set;
}

bitMap* setIntersection (bitMap* set1, bitMap* set2){
    bitMap *intersectionSet = createSet(MAX(set1->chunks,set2->chunks));
    intersectionSet->chunks =  MAX(set1->chunks,set2->chunks);
    unsigned int chunks = MIN(set1->chunks,set2->chunks);
    for(unsigned int i=0; i<chunks; i++){
        intersectionSet->bits[i] = set1->bits[i] & set2->bits[i];
    } 
    return intersectionSet;
}

unsigned int calculatePriority(bitMap* set){
    unsigned int totalPriority = 0;
    for(unsigned int i = 0; i < BITSTOTAL; i++){
        totalPriority += BITTEST(set->bits, i) ? i+1 : 0;
    }
    return totalPriority;
}

void printSet(bitMap* set){
    char visualSet[BITSTOTAL];
    for(unsigned int i=0; i<BITSTOTAL; i++){
        visualSet[i] = (BITTEST(set->bits,i)) ?  i + ((i<26) ? 'a': 'A' - 26) : ' '; 
    }
    printf("%s\n",visualSet);
}

int main(){
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    char *p;
    unsigned totalPriority = 0;
    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        p = strchr(buffer, '\n');
        if (p) {
            *p = '\0';
        }
        unsigned int backpackSize = strlen(buffer);
        printf("BackpackSize = %u\n",backpackSize);
        printf("Backpack insides = %s\n",buffer);
        bitMap* firstCompartment = createSet(BITNSLOTS(BITSTOTAL));
        bitMap* secondCompartment = createSet(BITNSLOTS(BITSTOTAL));
        for (unsigned int i=0; i<backpackSize/2; i++){
            setItem(firstCompartment,  buffer[i]);
            setItem(secondCompartment, buffer[(backpackSize/2)+i]);
        }
        bitMap* intersection = setIntersection(firstCompartment, secondCompartment);
        totalPriority += calculatePriority(intersection);
        printSet(firstCompartment);
        printSet(secondCompartment);
        printSet(intersection);
        printf("Backpack priority = %u\n\n", calculatePriority(intersection));
        free(firstCompartment);
        free(secondCompartment);
        free(intersection);
    }
    printf("%u\n",totalPriority);
}