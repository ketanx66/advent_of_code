#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

#define SPACE_AVAIL  70000000
#define SPACE_NEEDED 30000000

typedef enum PROCESSING{
    PENDING,
    ONGOING,
    FINISHED
} PROCESSING;

typedef struct DIRECTORY{
    unsigned int filesSize;
    unsigned int dirSize;
    unsigned int noOfDirs;
    char* name;
    PROCESSING state;
    struct DIRECTORY* parent;
    struct DIRECTORY** dirs;
} DIRECTORY;

DIRECTORY* home;

typedef struct INSTRUCTION{
    enum {CD,LS} code;
    union{
        struct{
            char* name;
        }dir;
    }data;
} INSTRUCTION;

INSTRUCTION parseInstruction(char* buffer){
    INSTRUCTION instr;
    if(buffer[2] == 'c'){
        instr.code = CD;
        instr.data.dir.name = strdup(&buffer[5]);
    }
    else if (buffer[2] == 'l'){
        instr.code = LS;
        instr.data.dir.name = NULL;
    }
    return instr;
}

DIRECTORY* processInstruction(INSTRUCTION instr, DIRECTORY* dir){
    switch (instr.code)
    {
    case CD:
        if(dir->state == ONGOING){
            dir->state = FINISHED; 
        } 
        if(!strcmp(home->name,instr.data.dir.name)){
            return home;
        }
        if(!strcmp("..",instr.data.dir.name)){
            return dir->parent;
        }
        for(unsigned int i=0;i<dir->noOfDirs;i++){
            if(!strcmp(dir->dirs[i]->name,instr.data.dir.name)){
                return dir->dirs[i];
            }
        }
        break;
    case LS:
        if(dir->state == PENDING){
            dir->state = ONGOING;
        }
        break;
    default:
        break;
    }
    return dir;
}

void addChildDir(DIRECTORY* dir, char* name){
    dir->noOfDirs++;
    dir->dirs = realloc(dir->dirs, sizeof(DIRECTORY) * dir->noOfDirs);
    dir->dirs[dir->noOfDirs-1] = malloc(sizeof(DIRECTORY));
    dir->dirs[dir->noOfDirs-1]->name = strdup(name);
    dir->dirs[dir->noOfDirs-1]->filesSize = 0;
    dir->dirs[dir->noOfDirs-1]->dirSize = 0;
    dir->dirs[dir->noOfDirs-1]->dirs = NULL;
    dir->dirs[dir->noOfDirs-1]->noOfDirs = 0;
    dir->dirs[dir->noOfDirs-1]->state = PENDING;
    dir->dirs[dir->noOfDirs-1]->parent = dir;
}

void updateStateOfDirs(DIRECTORY* dir, char* buffer){
    if(buffer[0]=='d'){
        addChildDir(dir,&buffer[4]);
        return;
    }
    if(dir->state == ONGOING){
        unsigned int fileSize;
        sscanf(buffer, "%d", &fileSize);
        dir->filesSize += fileSize;
        return;
    }
}

unsigned int calculateDirSize(DIRECTORY* dir){
    dir->dirSize = dir->filesSize;
    for(unsigned int i = 0; i<dir->noOfDirs; i++){
        dir->dirSize += calculateDirSize(dir->dirs[i]);
    }
    return dir->dirSize;
}

unsigned int calculateResult(DIRECTORY* dir, unsigned int filter){
    unsigned int result = (dir->dirSize >= filter) ? dir->dirSize : SPACE_AVAIL;
    for(unsigned int i = 0; i<dir->noOfDirs; i++){
        result = MIN(calculateResult(dir->dirs[i],filter),result);
    }
    return result;
}

int main(){
    char buffer[BUFFER_SIZE] = {0};
    char *p = NULL;
    FILE *input_fp = fopen("./input.txt", "r");
    if (input_fp == NULL){
        exit(EXIT_FAILURE);
    }

    home = malloc(sizeof(*home));
    home->filesSize = 0;
    home->dirSize = 0;
    home->name = "/";
    home->parent = home;
    home->state = PENDING;

    DIRECTORY* current_dir = home;

    INSTRUCTION instr;
    while(fgets(buffer, BUFFER_SIZE, input_fp)){
        p = strchr(buffer, '\n');
        if (p) {
            *p = '\0';
        }
        if (buffer[0] == '$'){
            instr = parseInstruction(buffer);
            current_dir = processInstruction(instr,current_dir);
        } else {
            updateStateOfDirs(current_dir,buffer);
        }
    }
    unsigned int freeMemory = SPACE_AVAIL - calculateDirSize(home);
    unsigned int needToFree = SPACE_NEEDED - freeMemory;
    printf("%u\n",calculateResult(home,needToFree));
}