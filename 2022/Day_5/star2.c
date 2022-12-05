#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

typedef struct CRATE
{
    struct CRATE* next;
    char tag;
} CRATE;

CRATE NULL_CRATE_OBJ = {NULL,'_'};
CRATE* NULL_CRATE = &NULL_CRATE_OBJ;
 
typedef struct STACK {
    CRATE* top;
} STACK;

CRATE* newCrate(char tag){
    CRATE* crate = malloc(sizeof(CRATE));
    crate->tag = tag;
    crate->next = NULL_CRATE;
    return crate;
}

void putCrate(STACK* stack, CRATE* crate){
    if(crate == NULL_CRATE){
        return;
    }
    CRATE* current_crate = stack->top;
    if(stack->top == NULL_CRATE){
        stack->top = crate;
        return;
    }
    CRATE* last_crate = NULL_CRATE;
    while(current_crate != NULL_CRATE){
        last_crate = current_crate;
        current_crate = current_crate->next;
    }
    last_crate->next = crate;
}

void pushCrate(STACK* stack, CRATE* crate){
    crate->next=stack->top;
    stack->top=crate;
}

CRATE* popCrate(STACK* stack){
    CRATE* crate = stack->top;
    stack->top = crate->next;
    crate->next = NULL_CRATE;
}

void moveNCrates(STACK* stackFrom, STACK* stackDest, unsigned int noOfCrates){
    CRATE* topCrate = stackFrom->top;
    CRATE* lastCrate = stackFrom->top;

    for(unsigned int i=1; i<noOfCrates; i++){
        lastCrate = lastCrate->next;
    }
    stackFrom->top = lastCrate->next;
    lastCrate->next = stackDest->top;
    stackDest->top = topCrate;

}

void printTopOfStacks(STACK* stacks,unsigned int noOfStacks){
    char* result = malloc(sizeof(char)*(noOfStacks+1));
    result[noOfStacks] = '\0';
    for (unsigned int i=0; i<noOfStacks; i++){
        result[i] = stacks[i].top->tag;
    }
    printf("%s\n",result);
}

int main(){
    char buffer[BUFFER_SIZE] = {0};
    char *p = NULL;
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }

    unsigned int string_len = 0;
    unsigned int noOfStacks = 0;
    STACK* stacks = NULL;

    fgets(buffer, BUFFER_SIZE, input_fp);
    p = strchr(buffer, '\n');
    if (p) {
        *p = '\0';
    }

    string_len = strlen(buffer);
    noOfStacks = (string_len+1)/4;
    stacks = malloc(sizeof(*stacks)*noOfStacks);
    for(unsigned int i=0; i<noOfStacks; i++){
        stacks[i].top = NULL_CRATE;
    }

    rewind(input_fp);

    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        p = strchr(buffer, '\n');
        if (p) {
            *p = '\0';
        }
        if(buffer[1]=='1'){
            break;
        }
        for(unsigned int i=0; i < noOfStacks; i++){
            char crateTag = buffer[(i*4)+1];
            if(crateTag >= 'A' && crateTag <= 'Z'){
                CRATE* new_crate = newCrate(crateTag);
                putCrate(&stacks[i],new_crate);
            }
        }
    }
    fgets(buffer, BUFFER_SIZE, input_fp);
    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        printTopOfStacks(stacks,noOfStacks);
        p = strchr(buffer, '\n');
        if (p) {
            *p = '\0';
        }
        unsigned int howManyToMove = 0;
        unsigned int stackFrom = 0;
        unsigned int stackTo = 0;
        sscanf(buffer,"move %d from %d to %d", &howManyToMove, &stackFrom, &stackTo);
        moveNCrates(&stacks[stackFrom-1],&stacks[stackTo-1],howManyToMove);
    }
    printTopOfStacks(stacks,noOfStacks);
}