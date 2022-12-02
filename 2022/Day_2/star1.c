#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 8

#define WIN  6
#define DRAW 3

typedef enum {ROCK,PAPER,SCISSORS,MOVES_COUNT} MOVE;
unsigned int move_score[MOVES_COUNT] = {[ROCK]     = 1,
                                        [PAPER]    = 2,
                                        [SCISSORS] = 3};

static inline MOVE char_to_move(char c){
    switch (c)
    {
    case 'A':
    case 'X':
        return ROCK;
    case 'B':
    case 'Y':
        return PAPER;
    case 'C':
    case 'Z':
        return SCISSORS;
    default:
        printf("Input is not valid, check if all moves are correct\n");
        exit(EXIT_FAILURE);
    }
}

static inline unsigned int match_outcome(MOVE opponent_move, MOVE my_move){
    unsigned int score = move_score[my_move];
    switch (opponent_move)
    {
    case ROCK:
        if(my_move == ROCK)
            score += DRAW;
        else if(my_move == PAPER)
            score += WIN;
        break;
    case PAPER:
        if(my_move == PAPER)
            score += DRAW;
        else if(my_move == SCISSORS)
            score += WIN;
        break;
    case SCISSORS:
        if(my_move == ROCK)
            score += WIN;
        else if(my_move == SCISSORS)
            score += DRAW;
        break;
    }
    return score;
}

int main(){
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    unsigned int score = 0;
    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        score += match_outcome(char_to_move(buffer[0]),
                               char_to_move(buffer[2]));
    }
    printf("%u\n",score);
}