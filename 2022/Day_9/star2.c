#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

#define KNOTS 10
#define TAIL KNOTS-1

typedef enum DIRECTION{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    UP_RIGHT,
    UP_LEFT,
    DOWN_RIGHT,
    DOWN_LEFT
} DIRECTION;

typedef struct MOVE{
    DIRECTION direction;
    unsigned int steps;
} MOVE;

typedef struct POSITION{
    int x;
    int y;
} POSITION;

typedef struct HISTORY{
    unsigned int noOfRecords;
    unsigned int capacity;
    POSITION* records;
} HISTORY;

DIRECTION getDiagonalDirection(DIRECTION dir1, DIRECTION dir2){
   switch (dir1)
    {
    case DOWN:
        if (dir2 == LEFT)
            return DOWN_LEFT;
        else if (dir2==RIGHT);
            return DOWN_RIGHT;    
        break;
    case UP:
        if (dir2 == LEFT)
            return UP_LEFT;
        else if (dir2==RIGHT);
            return UP_RIGHT;    
        break;
    case LEFT:
        if (dir2 == UP)
            return UP_LEFT;
        else if (dir2==DOWN);
            return DOWN_LEFT;    
        break;
    case RIGHT:
        if (dir2 == UP)
            return UP_RIGHT;
        else if (dir2==DOWN);
            return DOWN_RIGHT;    
        break;
    }
}

MOVE getMove(char *buffer){
    char c;
    MOVE move;
    sscanf(buffer,"%c %d",&c,&move.steps);
    switch (c)
    {
    case 'D':
        move.direction = DOWN;
        break;
    case 'U':
        move.direction = UP;
        break;
    case 'L':
        move.direction = LEFT;
        break;
    case 'R':
        move.direction = RIGHT;
        break;
    default:
        printf("Such letter (%c) is not a valid move\n",c);
        exit(EXIT_FAILURE);
        break;
    }
    return move;
}

void addPositionToHistory(HISTORY* his, POSITION pos){
    for(unsigned int i = 0; i<his->noOfRecords; i++){
        if(his->records[i].x == pos.x && his->records[i].y == pos.y)
            return;
    }
    if(his->capacity < his->noOfRecords){
        his->capacity *= 2;
        his->records = realloc(his->records,(sizeof (struct POSITION)) * his->capacity);
    }
    his->records[his->noOfRecords] = pos;
    his->noOfRecords++;
}

bool shouldTailMove(POSITION* h, POSITION *t){
    if(abs(h->x - t->x)>1 || abs(h->y - t->y)>1){
        return true;
    }
    return false;
}

void makeMoveInDirection(DIRECTION dir, POSITION* pos){
    switch (dir)
    {
    case DOWN:
        pos->y--;
        break;
    case UP:
        pos->y++;
        break;
    case LEFT:
        pos->x--;
        break;
    case RIGHT:
        pos->x++;
        break;
    case DOWN_LEFT:
        pos->y--;
        pos->x--;
        break;
    case DOWN_RIGHT:
        pos->y--;
        pos->x++;
        break;
    case UP_LEFT:
        pos->y++;
        pos->x--;
        break;
    case UP_RIGHT:
        pos->y++;
        pos->x++;
        break;
    }
}

void moveTail(POSITION *h, POSITION* t, HISTORY* tailHistory){
    int y_offset = h->y - t->y;
    int x_offset = h->x - t->x;
    
    DIRECTION dir;

    if(y_offset > 0){
        if(x_offset > 0)
            dir = UP_RIGHT;
        else if (x_offset == 0)
            dir = UP;
        else
            dir = UP_LEFT;
    }
    else if(y_offset == 0){
        if(x_offset > 0)
            dir = RIGHT; 
        else if(x_offset <0)
            dir = LEFT;
    }
    else{
        if(x_offset > 0)
            dir = DOWN_RIGHT;
        else if (x_offset == 0)
            dir = DOWN;
        else
            dir = DOWN_LEFT;
    }

    makeMoveInDirection(dir,t);
    if(tailHistory != NULL){
        addPositionToHistory(tailHistory,*t);
    }
}

void makeSingleMove(DIRECTION dir, POSITION* rope, HISTORY* tailHistory){
    makeMoveInDirection(dir,&rope[0]);
    for(unsigned int i = 1; i < KNOTS;i++)
    {
        if(shouldTailMove(&rope[i-1],&rope[i])){
            moveTail(&rope[i-1],&rope[i],(i==TAIL)?tailHistory:NULL);
        }
    }
}

void makeMove(MOVE move, POSITION* rope, HISTORY* tailHistory){
    while(move.steps>0){
        makeSingleMove(move.direction,rope,tailHistory);
        move.steps--;
    }
}

unsigned int getResult(HISTORY* his){
    return his->noOfRecords;
}

int main(){
    char buffer[BUFFER_SIZE] = {0};
    char *p = NULL;
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }
    POSITION rope[KNOTS] = {0};
    HISTORY historyTail;
    historyTail.capacity = 2000;
    historyTail.noOfRecords = 0;
    historyTail.records = malloc((sizeof (struct POSITION)) * historyTail.capacity);
    addPositionToHistory(&historyTail,rope[TAIL]);

    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        p = strchr(buffer, '\n');
        if (p) {
            *p = '\0';
        }
        MOVE move = getMove(buffer);
        makeMove(move,rope,&historyTail);
    }

    unsigned int result = getResult(&historyTail);
    printf("result=%u\n",result);
}