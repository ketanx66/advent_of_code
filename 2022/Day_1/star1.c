#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 255

int main(){
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];

    unsigned int elf_index = 1;
    unsigned int elf_total_calories=0;
    unsigned int max_calories = 0;
    unsigned int elf_with_max_calories = elf_index;
    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        unsigned int calories=0;
        if (sscanf(buffer,"%d", &calories)==1) {
            elf_total_calories += calories;
        }
        else {
            if (elf_total_calories > max_calories){
                elf_with_max_calories = elf_index;
                max_calories = elf_total_calories;
            }
            printf("elf(%u) total=%u\n",elf_index,elf_total_calories);
            elf_total_calories=0;
            elf_index++;
        }
    }
    if (elf_total_calories > max_calories){
        elf_with_max_calories = elf_index;
        max_calories = elf_total_calories;
    }
    printf("elf = %u\ncalories = %u\n",elf_with_max_calories, max_calories);
}