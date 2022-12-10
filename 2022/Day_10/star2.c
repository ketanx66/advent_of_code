#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))
#define LIT '#'
#define DARK '.'

typedef struct SCREEN{
    unsigned int width;
    unsigned int current_pixel;
} SCREEN;

typedef struct CPU{
    int x;
    int cycle;
    int signal;
    SCREEN screen;
} CPU;



void write_pixel(CPU *cpu){
    if(abs(cpu->screen.current_pixel-cpu->x)<2){
        putc(LIT,stdout);
    } else {
        putc(DARK,stdout);
    }
    cpu->screen.current_pixel++;
    if(cpu->screen.current_pixel == cpu->screen.width){
        cpu->screen.current_pixel = 0;
        putc('\n',stdout);
    }
}

void NOOP(CPU* cpu){
    cpu->cycle++;
    write_pixel(cpu);
}

void ADDX(CPU* cpu, int val){
    NOOP(cpu);
    NOOP(cpu);
    cpu->x += val;
}

int main(){
    char buffer[BUFFER_SIZE] = {0};
    char *p = NULL;
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }

    CPU cpu;
    cpu.x = 1;
    cpu.cycle = 0;
    cpu.signal = 0;
    cpu.screen.width = 40;
    cpu.screen.current_pixel = 0;

    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        p = strchr(buffer, '\n');
        if (p) {
            *p = '\0';
        }
        if(buffer[0]=='a'){
            int val=0;
            sscanf(buffer,"addx %d",&val);
            ADDX(&cpu, val);
        }
        else
            NOOP(&cpu);
    }
}