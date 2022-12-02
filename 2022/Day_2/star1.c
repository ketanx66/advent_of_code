#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 255

int main(){
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    while(fgets(buffer, BUFFER_SIZE, input_fp)){
   
    }
}