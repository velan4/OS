#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Block {
    int blockNumber;
    struct Block* next;
} Block;

typedef struct File {
    char name[20];
    Block* firstBlock;
    Block* lastBlock;
} File;

File* createFile(const char* name) {
    File* newFile = (File*)malloc(sizeof(File));
    strcpy(newFile->name, name);
    newFile->firstBlock = NULL;
    newFile->lastBlock = NULL;
    return newFile;
}

void addBlock(File* file, int blockNumber) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->blockNumber = blockNumber;
    newBlock->next = NULL;

    if (file->lastBlock == NULL) {
        file->firstBlock = newBlock;
        file->lastBlock = newBlock;
    } else {
        file->lastBlock->next = newBlock;
        file->lastBlock = newBlock;
    }
}

void displayFile(File* file) {
    printf("File: %s\n", file->name);
    Block* current = file->firstBlock;
    while (current != NULL) {
        printf("Block Number: %d\n", current->blockNumber);
        current = current->next;
    }
}

void freeFile(File* file) {
    Block* current = file->firstBlock;
    Block* nextBlock;
    while (current != NULL) {
        nextBlock = current->next;
        free(current);
        current = nextBlock;
    }
    free(file);
}

int main() {
    File* myFile = createFile("example.txt");
    addBlock(myFile, 1);
    addBlock(myFile, 3);
    addBlock(myFile, 5);
    
    displayFile(myFile);
    
    freeFile(myFile);
    return 0;
}
