#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 255
unsigned int top_three_calories[3];
void push_calories(unsigned int calories){
    if(calories >= top_three_calories[0]){
        top_three_calories[2] = top_three_calories[1];
        top_three_calories[1] = top_three_calories[0];
        top_three_calories[0] = calories;
    } 
    else if(calories >= top_three_calories[1]){
        top_three_calories[2] = top_three_calories[1];
        top_three_calories[1] = calories;
    }
    else if(calories >= top_three_calories[2]){
        top_three_calories[2] = calories;
    }
}

int main(){
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    unsigned int elf_total_calories = 0;

    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        unsigned int calories=0;
        if (sscanf(buffer,"%d", &calories)==1) {
            elf_total_calories += calories;
        }
        else {
            push_calories(elf_total_calories);
            elf_total_calories=0;
        }
    }
    push_calories(elf_total_calories);
    unsigned int combined_calories = top_three_calories[0] +
                                     top_three_calories[1] +
                                     top_three_calories[2];
    printf("top three %u %u %u\n", top_three_calories[0], top_three_calories[1], top_three_calories[2]);
    printf("calories = %u\n", combined_calories);
}