#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 8

typedef enum {ROCK,PAPER,SCISSORS,MOVES_COUNT} MOVE;
typedef enum {WIN,DRAW,LOSE,STRATEGY_COUNT} STRATEGY;
unsigned int move_score[MOVES_COUNT] = {[ROCK]     = 1,
                                        [PAPER]    = 2,
                                        [SCISSORS] = 3};
unsigned int strategy_score[STRATEGY_COUNT] = {[WIN]  = 6,
                                               [DRAW] = 3,
                                               [LOSE] = 0};

static inline MOVE char_to_move(char c){
    switch (c)
    {
    case 'A':
        return ROCK;
    case 'B':
        return PAPER;
    case 'C':
        return SCISSORS;
    default:
        printf("Input is not valid, check if all moves are correct\n");
        exit(EXIT_FAILURE);
    }
}
static inline STRATEGY char_to_strategy(char c){
    switch (c)
    {
    case 'X':
        return LOSE;
    case 'Y':
        return DRAW;
    case 'Z':
        return WIN;
    default:
        printf("Input is not valid, check if all moves are correct\n");
        exit(EXIT_FAILURE);
    }
}

static inline unsigned int match_outcome(MOVE opponent_move, STRATEGY my_strategy){
    unsigned int score = strategy_score[my_strategy];
    switch (opponent_move)
    {
    case ROCK:
        if(my_strategy == WIN)
            score += move_score[PAPER];
        else if(my_strategy == DRAW)
            score += move_score[ROCK];
        else if(my_strategy == LOSE)
            score += move_score[SCISSORS];
        break;
    case PAPER:
        if(my_strategy == WIN)
            score += move_score[SCISSORS];
        else if(my_strategy == DRAW)
            score += move_score[PAPER];
        else if(my_strategy == LOSE)
            score += move_score[ROCK];
        break;
    case SCISSORS:
        if(my_strategy == WIN)
            score += move_score[ROCK];
        else if(my_strategy == DRAW)
            score += move_score[SCISSORS];
        else if(my_strategy == LOSE)
            score += move_score[PAPER];
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
                               char_to_strategy(buffer[2]));
    }
    printf("%u\n",score);
}