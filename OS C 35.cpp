#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 10
#define BLOCK_SIZE 512

typedef struct {
    int blockNumber;
    char data[BLOCK_SIZE];
} Block;

typedef struct {
    Block blocks[MAX_FILES];
    int blockCount;
} FileSystem;

void initializeFileSystem(FileSystem *fs) {
    fs->blockCount = 0;
}

int allocateBlock(FileSystem *fs, const char *data) {
    if (fs->blockCount >= MAX_FILES) {
        return -1; // No more space
    }
    fs->blocks[fs->blockCount].blockNumber = fs->blockCount;
    snprintf(fs->blocks[fs->blockCount].data, BLOCK_SIZE, "%s", data);
    fs->blockCount++;
    return fs->blockCount - 1; // Return block index
}

void displayFileSystem(const FileSystem *fs) {
    for (int i = 0; i < fs->blockCount; i++) {
        printf("Block %d: %s\n", fs->blocks[i].blockNumber, fs->blocks[i].data);
    }
}

int main() {
    FileSystem fs;
    initializeFileSystem(&fs);

    allocateBlock(&fs, "File 1 Data");
    allocateBlock(&fs, "File 2 Data");
    allocateBlock(&fs, "File 3 Data");

    displayFileSystem(&fs);

    return 0;
}
