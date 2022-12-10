#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))
#define FIRST_MEASURMENT 20
#define MEASURMENT_PERIOD 40

typedef struct CPU{
    int x;
    int cycle;
    int signal;    
} CPU;

void check_signal(CPU *cpu){
    if ((cpu->cycle>=20) &&
        (((cpu->cycle-20)%40)==0))
    {
        cpu->signal += cpu->cycle*cpu->x;
    }
}

void NOOP(CPU* cpu){
    cpu->cycle++;
    check_signal(cpu);
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

    printf("%u\n",cpu.signal);
}