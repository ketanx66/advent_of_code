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

bool visibleInCol(unsigned int col, unsigned int position){
    uint8_t max_height = grid[0][col];
    uint8_t h = grid[position][col]; 
    for(unsigned int i = 0; i < position; i++){
        max_height = MAX(max_height,grid[i][col]);
    }
    if (max_height < h)
        return true;
    max_height = grid[N-1][col];
    for(unsigned int i = position+1; i < N; i++){
        max_height = MAX(max_height,grid[i][col]);
    }
    return max_height<h;
}
bool visibleInRow(unsigned int row, unsigned int position){
    uint8_t max_height = grid[row][0];
    uint8_t h = grid[row][position]; 
    for(unsigned int i = 0; i < position; i++){
        max_height = MAX(max_height,grid[row][i]);
    }
    if (max_height < h)
        return true;
    max_height = grid[row][N-1];
    for(unsigned int i = position+1; i < N; i++){
        max_height = MAX(max_height,grid[row][i]);
    }
    return max_height<h;
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
            int h = grid[i][j];
            if(i==0 || i == N-1 || j == 0 || j== N-1||
               visibleInCol(j,i)||
               visibleInRow(i,j))
                result++;
        }
    }
    printf("%u\n",result);
}