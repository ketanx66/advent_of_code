#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))
#define N 99

int8_t grid[N][N];

unsigned int visibleUp(unsigned int row, unsigned int col){
    uint8_t h = grid[row][col];
    unsigned int visibility = 0;
    for(int i = row-1; i >= 0; i--){
        visibility++;
        if(grid[i][col] >= h)
            break;
    }
    return visibility;
}
unsigned int visibleDown(unsigned int row, unsigned int col){
    uint8_t h = grid[row][col];
    unsigned int visibility = 0;
    for(int i = row+1; i < N; i++){
        visibility++;
        if(grid[i][col] >= h)
            break;
    }
    return visibility;
}
unsigned int visibleLeft(unsigned int row, unsigned int col){
    uint8_t h = grid[row][col];
    unsigned int visibility = 0;
    for(int i = col-1; i >= 0; i--){
        visibility++;
        if(grid[row][i] >= h)
            break;
    }
    return visibility;
}
unsigned int visibleRight(unsigned int row, unsigned int col){
    uint8_t h = grid[row][col];
    unsigned int visibility = 0;
    for(int i = col+1; i < N; i++){
        visibility++;
        if(grid[row][i] >= h)
            break;
    }
    return visibility;
}

int main(){
    char buffer[BUFFER_SIZE] = {0};
    char *p = NULL;
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }
    

    unsigned int row = 0;
    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        p = strchr(buffer, '\n');
        if (p) {
            *p = '\0';
        }
        for(unsigned int col = 0; col<N; col++){
            grid[row][col] = buffer[col] - '0';
        }
        row++;
    }

    unsigned int result = 0;
    for(unsigned int i = 0; i<N;i++){
        for(unsigned int j =0; j<N;j++){
            result = MAX(result,
                         visibleUp(i,j)*
                         visibleDown(i,j)*
                         visibleLeft(i,j)*
                         visibleRight(i,j));
        }
    }
    printf("%u\n",result);
}